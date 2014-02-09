namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner)
    {
    }

    template<typename T,typename U>
    M2MQuerySet<ManyToMany<T,U>,T,U> ManyToMany<T,U>::query(Bdd& bdd)const
    {
        return M2MQuerySet<ManyToMany<T,U>,T,U>(*this,bdd);
    }

    template<typename T,typename U>
    std::list<typename Cache<U>::type_ptr> ManyToMany<T,U>::all(Bdd& bdd,int max_depth) const
    {
        std::list<typename Cache<U>::type_ptr> results;
        query(bdd).get(results,max_depth);
        return results;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::nameAttrs(std::string& q_str,int max_depth,Bdd& bdd)
    {
        U::nameAttrs(q_str,_related,max_depth,bdd);
    }
    
    template<typename T,typename U>
    void ManyToMany<T,U>::nameTables(std::string& q_str,int max_depth,Bdd& bdd)
    {
        q_str+= bdd.escapeColumn(table)+" AS "+bdd.escapeColumn(table);
        makeJoin(q_str,max_depth,bdd);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::makeJoin(std::string& q_str,int max_depth,Bdd& bdd)
    {
        const std::string table_alias_T = JOIN_ALIAS(table,_owner);

        q_str+=
            "\nLEFT JOIN "+T::table+" AS "+table_alias_T
            +" ON ("
            +bdd.escapeColumn(table)+"."+bdd.escapeColumn(_owner)
            +" = "+bdd.escapeColumn(table_alias_T)+"."+bdd.escapeColumn("id")
            +")\nLEFT JOIN "+U::table+" AS "+_related
            +" ON ("
            +bdd.escapeColumn(table)+"."+bdd.escapeColumn(_linked)
            +" = "+bdd.escapeColumn(_related)+"."+bdd.escapeColumn("id")
            +")";

        U::makeJoin(q_str,_related,max_depth,bdd);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const typename Cache<U>::type_ptr& obj,Bdd& bdd)
    {
        add(*obj,bdd);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const U& obj,Bdd& bdd)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;
        
        std::string q_str = "INSERT INTO "+bdd.escapeColumn(table)
            +"("+_owner+","+_linked+") VALUES ((?),(?));";

        Query& q = *bdd.prepareQuery(q_str);
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
    void ManyToMany<T,U>::remove(const typename Cache<U>::type_ptr& obj,Bdd& bdd)
    {
        remove(*obj,bdd);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const U& obj,Bdd& bdd)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;

        const std::string table_escaped = bdd.escapeColumn(table);
        
        std::string q_str = "DELETE FROM "+table_escaped+" WHERE ("
            +table_escaped+"."+bdd.escapeColumn(_owner)+" = (?)"
            +" AND "
            +table_escaped+"."+bdd.escapeColumn(_linked)+" = (?))";

        Query& q = *bdd.prepareQuery(q_str);
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
