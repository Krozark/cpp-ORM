namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner)
    {
    }

    template<typename T,typename U>
    M2MQuerySet<ManyToMany<T,U>,T,U> ManyToMany<T,U>::query(DB& db)const
    {
        return M2MQuerySet<ManyToMany<T,U>,T,U>(*this,db);
    }

    template<typename T,typename U>
    std::list<typename Cache<U>::type_ptr> ManyToMany<T,U>::all(DB& db,int max_depth) const
    {
        std::list<typename Cache<U>::type_ptr> results;
        query(db).get(results,max_depth);
        return results;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::nameAttrs(std::string& q_str,int max_depth,DB& db)
    {
        U::nameAttrs(q_str,_related,max_depth,db);
    }
    
    template<typename T,typename U>
    void ManyToMany<T,U>::nameTables(std::string& q_str,int max_depth,DB& db)
    {
        q_str+= db.escapeColumn(table)+" AS "+db.escapeColumn(table);
        makeJoin(q_str,max_depth,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::makeJoin(std::string& q_str,int max_depth,DB& db)
    {
        const std::string table_alias_T = JOIN_ALIAS(table,_owner);

        q_str+=
            "\nLEFT JOIN "+T::table+" AS "+table_alias_T
            +" ON ("
            +db.escapeColumn(table)+"."+db.escapeColumn(_owner)
            +" = "+db.escapeColumn(table_alias_T)+"."+db.escapeColumn("id")
            +")\nLEFT JOIN "+U::table+" AS "+_related
            +" ON ("
            +db.escapeColumn(table)+"."+db.escapeColumn(_linked)
            +" = "+db.escapeColumn(_related)+"."+db.escapeColumn("id")
            +")";

        U::makeJoin(q_str,_related,max_depth,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const typename Cache<U>::type_ptr& obj,DB& db)
    {
        add(*obj,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const U& obj,DB& db)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;
        
        std::string q_str = "INSERT INTO "+db.escapeColumn(table)
            +"("+_owner+","+_linked+") VALUES ((?),(?));";

        Query& q = *db.prepareQuery(q_str);
        q.set(owner.pk,1);
        q.set(obj.pk,2);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<BLEU<<"[Sql:insert]"<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<BLANC<<std::endl;
        #endif
        
        q.execute();
        q.next();
        delete &q;

    };

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const typename Cache<U>::type_ptr& obj,DB& db)
    {
        remove(*obj,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const U& obj,DB& db)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;

        const std::string table_escaped = db.escapeColumn(table);
        
        std::string q_str = "DELETE FROM "+table_escaped+" WHERE ("
            +table_escaped+"."+db.escapeColumn(_owner)+" = (?)"
            +" AND "
            +table_escaped+"."+db.escapeColumn(_linked)+" = (?))";

        Query& q = *db.prepareQuery(q_str);
        q.set(owner.pk,1);
        q.set(obj.pk,2);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<COMMENTAIRE<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<BLANC<<std::endl;
        #endif
        
        q.execute();
        q.next();
        delete &q;

    };
}
