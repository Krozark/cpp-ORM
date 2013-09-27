namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner), modify(false)
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
        q_str+= bdd_used->escapecolumn(table)+" AS "+bdd_used->escapecolumn(table);
        makeJoin(q_str,max_depth);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::makeJoin(std::string& q_str,/*const std::string& prefix,*/int max_depth)
    {
        const std::string table_alias_T = JOIN_ALIAS(table,_owner);

        q_str+=
            "\nLEFT JOIN "+T::table+" AS "+table_alias_T
            +" ON ("
            +bdd_used->escapecolumn(table)+"."+bdd_used->escapecolumn(_owner)
            +" = "+bdd_used->escapecolumn(table_alias_T)+"."+bdd_used->escapecolumn("id")
            +")\nLEFT JOIN "+U::table+" AS "+_related
            +" ON ("
            +bdd_used->escapecolumn(table)+"."+bdd_used->escapecolumn(_linked)
            +" = "+bdd_used->escapecolumn(_related)+"."+bdd_used->escapecolumn("id")
            +")";

        U::makeJoin(q_str,_related,max_depth);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const U& obj)
    {
        /*modify = true;
        if(obj.pk==-1)
            obj.save();
        
        std::string q_str = "INSERT INTO "+bdd_used->escapeColum(table)
            +"("+_owner+","+_linked+") VALUES ((?),(?));";

        Query* q = bdd_used->prepareQuery(q_str);
        q->set(owner.pk,_owner);
        q->set(obj.pk,_linked);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<"\033[33m"<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<std::endl;
        #endif
        
        bdd_used->executeQuery(*q);
        delete q;

        linked.emplace_back(obj);*/
    };
}
