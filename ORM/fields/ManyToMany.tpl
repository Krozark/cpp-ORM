namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner)
    {
    }

    template<typename T,typename U>
    M2MQuerySet<ManyToMany<T,U>,T,U> ManyToMany<T,U>::query()
    {
        return M2MQuerySet<ManyToMany<T,U>,T,U>(*this);
    }

    template<typename T,typename U>
    std::list<typename Cache<U>::type_ptr> ManyToMany<T,U>::all(int max_depth)
    {
        std::list<typename Cache<U>::type_ptr> results;
        query().get(results,max_depth);
        return results;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::nameAttrs(std::string& q_str,int max_depth)
    {
        U::nameAttrs(q_str,_related,max_depth);
    }
    
    template<typename T,typename U>
    void ManyToMany<T,U>::nameTables(std::string& q_str,int max_depth)
    {
        q_str+= bdd_used->escapeColumn(table)+" AS "+bdd_used->escapeColumn(table);
        makeJoin(q_str,max_depth);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::makeJoin(std::string& q_str,int max_depth)
    {
        const std::string table_alias_T = JOIN_ALIAS(table,_owner);

        q_str+=
            "\nLEFT JOIN "+T::table+" AS "+table_alias_T
            +" ON ("
            +bdd_used->escapeColumn(table)+"."+bdd_used->escapeColumn(_owner)
            +" = "+bdd_used->escapeColumn(table_alias_T)+"."+bdd_used->escapeColumn("id")
            +")\nLEFT JOIN "+U::table+" AS "+_related
            +" ON ("
            +bdd_used->escapeColumn(table)+"."+bdd_used->escapeColumn(_linked)
            +" = "+bdd_used->escapeColumn(_related)+"."+bdd_used->escapeColumn("id")
            +")";

        U::makeJoin(q_str,_related,max_depth);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const typename Cache<U>::type_ptr& obj)
    {
        add(*obj);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const U& obj)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;
        
        std::string q_str = "INSERT INTO "+bdd_used->escapeColumn(table)
            +"("+_owner+","+_linked+") VALUES ((?),(?));";

        Query& q = *bdd_used->prepareQuery(q_str);
        q.set(owner.pk,1);
        q.set(obj.pk,2);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<BLEU<<"[SQL:insert]"<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<BLANC<<std::endl;
        #endif
        
        q.execute();
        q.next();
        delete &q;

    };

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const typename Cache<U>::type_ptr& obj)
    {
        remove(*obj);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const U& obj)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;

        const std::string table_escaped = bdd_used->escapeColumn(table);
        
        std::string q_str = "DELETE FROM "+table_escaped+" WHERE ("
            +table_escaped+"."+bdd_used->escapeColumn(_owner)+" = (?)"
            +" AND "
            +table_escaped+"."+bdd_used->escapeColumn(_linked)+" = (?))";

        Query& q = *bdd_used->prepareQuery(q_str);
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
