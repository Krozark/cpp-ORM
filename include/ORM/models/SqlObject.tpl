#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/QuerySet.hpp>

namespace orm
{

    ///////////////// functions ////////////////

    template<typename T>
    SqlObject<T>::SqlObject()
    {
    };

    template<typename T>
    template<typename ... Args>
    typename SqlObject<T>::pointer SqlObject<T>::create(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    typename SqlObject<T>::pointer SqlObject<T>::createFromDB(const Query& query,int& prefix, int max_depth)
    {
        SqlObject<T>::pointer res(new T());
        if(not res->_loadFromDB(query,prefix,max_depth))
        {
            res = SqlObject<T>::pointer(nullptr);
        }
	    return res;
    };

    template<typename T>
    typename SqlObject<T>::pointer SqlObject<T>::get(const unsigned int& id,DB& db,int max_depth)
    {
        return _cache.getOrCreate(id,db,max_depth);
    }

    template<typename T>
    typename SqlObject<T>::pointer SqlObject<T>::_getPointer(const unsigned int id,DB& db,int max_depth)
    {
        if(max_depth <0)
            return 0;

        std::string q_str ="SELECT ";
        _staticNameAttrs(q_str,_table,max_depth,db);

        q_str+="\nFROM ";
        _staticNameTables(q_str,"",max_depth,db);

        q_str+=" \nWHERE ("
        +db._escapeColumn(_table)+"."
        +db._escapeColumn(SqlObjectBase::ORM_MAKE_NAME(pk))
        +" = "+std::to_string(id)
        +") ";

        std::shared_ptr<Query> q(db.query(q_str));

        SqlObject<T>::pointer res(new T());
        if(not q->_getObj(*res,max_depth))
        {
            #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
            std::cerr<<ORM_COLOUR_RED<<"[GET OBJ] SqlObject<T>::_getPointer(const unsigned int id,int max_depth) failed"<<ORM_COLOUR_NONE<<std::endl;
            #endif
            res = SqlObject<T>::pointer(nullptr);
        }
        return res;
    };

    template<typename T>
    typename SqlObject<T>::pointer_array SqlObject<T>::all(DB& db,int max_depth)
    {
        pointer_array results;
        query(db).get(results,max_depth);
        return results;
    };

    template<typename T>
    QuerySet<T> SqlObject<T>::query(DB& db)
    {
        return QuerySet<T>(db);
    }


    template<typename T>
    bool SqlObject<T>::save(bool recursive,DB& db)
    {
        bool res = true;
        if(recursive)//save all FK
        {
            for(VFK* fk : _fkAttributsVector)
                fk->save(recursive,db);
        }
        else//save or create all FK needed (not null)
        {
            for(VFK* fk : _fkAttributsVector)
            {
                VFK& fk_tmp = *fk;
                if(fk_tmp._nullable == false and (fk_tmp._fk <=0 or fk_tmp._modified == true))
                {
                    fk_tmp.save(recursive,db);
                }
            }
        }

        if(pk <= 0)
        {

            _beforeSave();
            res = db._save(_table,pk,_attributsVector);
            if(res)
            {
                pointer ptr = this->asPointer();
                _cache._add(ptr);
                _afterSave();
            }
        }
        else
        {
            _beforeUpdate();
            res= db._update(_table,pk,_attributsVector);
            if(res)
                _afterUpdate();
        }
        return res;
    }

    template<typename T>
    bool SqlObject<T>::del(bool recursive,DB& db)
    {
        bool res =true;
        if(db._del(_table,pk))
        {
            _cache._del(pk);
            pk = -1;
            if(recursive)
            {
                for(VFK* fk : _fkAttributsVector)
                {
                    bool tmp = fk->del(recursive,db);
                    res = res && tmp;
                }
            }
            return res;
        }
        return false;
    };

    template<typename T>
    typename SqlObject<T>::pointer SqlObject<T>::asPointer()
    {
        return this->shared_from_this();
    }

    template<typename T>
    bool SqlObject<T>::createTable(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_CREATE_TABLE
        std::cerr<<ORM_COLOUR_MAGENTA<<"[CREATE] create table "<<_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
        return db.create(_table,_staticAttributsVector);
    }

    template<typename T>
    bool SqlObject<T>::dropTable(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_DROP_TABLE
        std::cerr<<ORM_COLOUR_MAGENTA<<"[DROP] drop table "<<_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
        _cache.clear(true);
        return db.drop(_table);
    }

    template<typename T>
    bool SqlObject<T>::clearTable(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_TRUNCATE_TABLE
        std::cerr<<ORM_COLOUR_MAGENTA<<"[TRUNCATE] truncate table "<<_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
        _cache.clear(true);
        return db.clear(_table);
    }

    template<typename T>
    const std::string& SqlObject<T>::getTable()const
    {
        return _table;
    }

    template<typename T>
    DB& SqlObject<T>::getDefaultDataBase()const
    {
        return DataBaseMixin<SqlObject<T>>::staticGetDefaultDataBase();
    }


    template<typename T>
    void SqlObject<T>::_staticNameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)
    {
        q_str+= db._escapeColumn(prefix)+"."+db._escapeColumn(SqlObjectBase::ORM_MAKE_NAME(pk))+" AS "+JOIN_ALIAS(prefix,SqlObjectBase::ORM_MAKE_NAME(pk));

        const int size = _staticAttributsVector.size();

        for(int i=0;i<size;++i)
        {
            q_str+= _staticAttributsVector[i]->_makeName(db,prefix,max_depth);
        }
    }

    template<typename T>
    void SqlObject<T>::_staticNameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)
    {
        const std::string table_alias = MAKE_PREFIX(prefix,_table);
        const std::string escaped_table_alias = db._escapeColumn(table_alias);

        q_str+=escaped_table_alias+" AS "+escaped_table_alias;

        if(--max_depth>=0)
            _staticMakeJoin(q_str,table_alias,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::_staticMakeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)
    {
        const int size = _staticFksAttributsVector.size();
        --max_depth;
        for(int i=0;i<size;++i)
        {

            const SqlObjectBase& object = _staticFksAttributsVector[i]->_getObject(db);
            /*if (&object == NULL)
                continue;*/
            const std::string& col = _staticFksAttributsVector[i]->getColumn();
            const std::string table_alias = MAKE_PREFIX(prefix,col);

            q_str+= "\nLEFT JOIN "+object.getTable()+" AS "+table_alias
                +" ON ("
                +db._escapeColumn(prefix)+"."+db._escapeColumn(col)
                +" = "+db._escapeColumn(table_alias)+"."+db._escapeColumn(SqlObjectBase::ORM_MAKE_NAME(pk))
                +")";

            if(max_depth>=0)
                object._makeJoin(q_str,table_alias,max_depth,db);
        }
    }

    template<typename T>
    void SqlObject<T>::_nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
        SqlObject<T>::_staticNameAttrs(q_str,prefix,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::_nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
        SqlObject<T>::_staticNameTables(q_str,prefix,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::_makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
        SqlObject<T>::_staticMakeJoin(q_str,prefix,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::_incDepth(int& depth,int max_depth)
    {
        depth+= (1 + _staticAttributsVector.size()); //id + attrs

        const int _size = _staticFksAttributsVector.size();
        for(int i=0;i<_size;++i)
            _staticFksAttributsVector[i]->_incDepth(depth,max_depth);
    }

};
