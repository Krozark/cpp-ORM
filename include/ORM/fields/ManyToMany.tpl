namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& o) :
    _owner(o),
    _adds(true)
    {
    }

    template<typename T,typename U>
    typename ManyToMany<T,U>::query_type ManyToMany<T,U>::query(DB& db)
    {
        return query_type(db);
    }

    template<typename T,typename U>
    typename ManyToMany<T,U>::query_type ManyToMany<T,U>::queryOwner(DB& db)const
    {
        query_type q = this->query(db);
        q.filter(
            Q<ManyToMany<T,U>>(
                this->_owner.pk,
                op::exact,
                ManyToMany<T,U>::ORM_MAKE_NAME(_owner)
            )
        );
        return q;
    }

    template<typename T,typename U>
    typename U::pointer_array ManyToMany<T,U>::all(DB& db,int max_depth)
    {
        if(this->_adds)
        {
            this->clearCache();
            this->queryOwner(db).get(this->_cache, max_depth);
        }
        return this->_cache;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::_nameAttrs(std::string& q_str,int max_depth,DB& db)
    {
        U::_staticNameAttrs(q_str,ORM_MAKE_NAME(_related),max_depth,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::_nameTables(std::string& q_str,int max_depth,DB& db)
    {
        q_str+= db._escapeColumn(_table)+" AS "+db._escapeColumn(_table);
        _makeJoin(q_str,max_depth,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::_makeJoin(std::string& q_str,int max_depth,DB& db)
    {
        const std::string table_alias_T = JOIN_ALIAS(_table,ORM_MAKE_NAME(_owner));

        q_str+=
            "\nLEFT JOIN "+T::_table+" AS "+table_alias_T
            +" ON ("
            +db._escapeColumn(_table)+"."+db._escapeColumn(ORM_MAKE_NAME(_owner))
            +" = "+db._escapeColumn(table_alias_T)+"."+db._escapeColumn(T::ORM_MAKE_NAME(pk))
            +")\nLEFT JOIN "+U::_table+" AS "+ORM_MAKE_NAME(_related)
            +" ON ("
            +db._escapeColumn(_table)+"."+db._escapeColumn(ORM_MAKE_NAME(_linked))
            +" = "+db._escapeColumn(ORM_MAKE_NAME(_related))+"."+db._escapeColumn(U::ORM_MAKE_NAME(pk))
            +")";

        U::_staticMakeJoin(q_str,ORM_MAKE_NAME(_related),max_depth,db);
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::add(const typename U::pointer& obj,DB& db)
    {
        if(_owner.pk <=0)
        {
            ORM_PRINT_ERROR("The M2M owner as not be saved")
            return false;
        }
        if(obj->pk<=0)
        {
            ORM_PRINT_ERROR("The object must be save to be add in a M2M")
            return false;
        }
        std::string q_str = "INSERT INTO "+db._escapeColumn(_table)
            +"("+ORM_MAKE_NAME(_owner)+","+ORM_MAKE_NAME(_linked)+") VALUES ((?),(?));";
        std::shared_ptr<Query> q(db.prepareQuery(q_str));
        q->_set(_owner.pk,db._getInitialSetcolumnNumber());
        q->_set(obj->pk,db._getInitialSetcolumnNumber()+1);
        #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<ORM_COLOUR_BLUE<<"[Sql:insert]"<<q_str<<"\nVALUES = ("<<_owner.pk<<", "<<obj->pk<<")"<<ORM_COLOUR_NONE<<std::endl;
        #endif
        q->_execute();
        q->_next();
        _adds = true;
        _cache.emplace_back(obj);
        return true;
    }

    /*template<typename T,typename U>
    bool ManyToMany<T,U>::add(const U& obj,DB& db)
    {
    };*/

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const typename U::pointer& obj,DB& db)
    {
        remove(*obj,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const U& obj,DB& db)
    {
        if(obj.pk<=0 or _owner.pk <=0)
            return;

        const std::string table_escaped = db._escapeColumn(_table);

        std::string q_str = "DELETE FROM "+table_escaped+" WHERE ("
            +table_escaped+"."+db._escapeColumn(ORM_MAKE_NAME(_owner))+" = (?)"
            +" AND "
            +table_escaped+"."+db._escapeColumn(ORM_MAKE_NAME(_linked))+" = (?))";

        std::shared_ptr<Query> q = db.prepareQuery(q_str);
        q->_set(_owner.pk,db._getInitialSetcolumnNumber());
        q->_set(obj.pk,db._getInitialSetcolumnNumber()+1);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<ORM_COLOUR_COMMENTS<<q_str<<"\nVALUES = ("<<_owner.pk<<", "<<obj.pk<<")"<<ORM_COLOUR_NONE<<std::endl;
        #endif

        q->_execute();
        q->_next();
        this->_adds = true;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::clearCache()
    {
        this->_cache.clear();
        this->_adds = false;
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::createTable(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_CREATE_TABLE
        std::cerr<<ORM_COLOUR_MAGENTA<<"[CREATE] create table "<<_table<<ORM_COLOUR_NONE<<std::endl;
        #endif

        static std::vector<const VAttr*> _staticAttributsVector = {
            new FK<T,false>(ORM_MAKE_NAME(_owner)),
            new FK<U,false>(ORM_MAKE_NAME(_linked))
        }; ///< attr of the class
        bool res = db.create(_table,_staticAttributsVector);
        delete reinterpret_cast<const FK<T,false>*>(_staticAttributsVector[0]);
        delete reinterpret_cast<const FK<U,false>*>(_staticAttributsVector[1]);

        return res;
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::dropTable(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_DROP_TABLE
        std::cerr<<ORM_COLOUR_MAGENTA<<"[DROP] drop table "<<_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
        return db.drop(_table);
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::clearTable(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_TRUNCATE_TABLE
        std::cerr<<ORM_COLOUR_MAGENTA<<"[TRUNCATE] truncate table "<<_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
        return db.clear(_table);
    }

    /*
    template <typename OWNER,typename LINKED,typename T, typename ... Args>
    FilterSet<ManyToMany<OWNER,LINKED>> M2MQ(T&& value,Args&& ... args)
    {
        return FilterSet<ManyToMany<OWNER,LINKED>>(Filter<ManyToMany<OWNER,LINKED>,T>(std::forward<T>(value),std::forward<Args>(args)...));
    }
    */
}
