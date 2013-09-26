namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner), modify(false)
    {
    }

    template<typename T,typename U>
    M2MQuerySet<ManyToMany<T,U>,T,U> ManyToMany<T,U>::query()
    {
        return M2MQuerySet<ManyToMany<T,U>,T,U>();
    }

    /*SELECT perso_spell.spell_id, perso_spell.perso_id,
      perso.id, perso.name,
      spell.name, spell.element
      FROM perso_spell
      LEFT JOIN perso  ON  (perso_spell.perso_id = perso.id)
      LEFT JOIN spell ON (perso_spell.spell_id = spell.id)
      WHERE (perso_spell.perso_id = 1)
      */
    template<typename T,typename U>
    void ManyToMany<T,U>::nameAttrs(std::string& q_str,/*const std::string& prefix,*/int max_depth)
    {
        q_str+= bdd_used->escapecolumn(table)+"."+bdd_used->escapecolumn("id")
            +" AS "+JOIN_ALIAS(table,"id")
            +", "+bdd_used->escapecolumn(table)+"."+bdd_used->escapecolumn(_owner)
            +" AS "+JOIN_ALIAS(table,_owner)
            +", "+bdd_used->escapecolumn(table)+"."+bdd_used->escapecolumn(_linked)
            +" AS "+JOIN_ALIAS(table,_linked)+", ";

        U::nameAttrs(q_str,JOIN_ALIAS(table,_linked),max_depth);
    }
    
    template<typename T,typename U>
    void ManyToMany<T,U>::nameTables(std::string& q_str,/*const std::string& prefix,*/int max_depth)
    {
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::makeJoin(std::string& q_str,/*const std::string& prefix,*/int max_depth)
    {
    }

    /*template<typename T,typename U>
    const std::list<std::shared_ptr<U> >& ManyToMany<T,U>::all()
    {
        if(linked.size() == 0 or modify)
        {
            std::string q_str="SELECT "
                //owner (juste pk)
                +bdd_used->escapeColum(T::table)+"."+bdd_used->escapeColum("id")
                +" AS "+bdd_used->escapeValue(T::table+".id");
            q_str+=", ";

            //linked(all)
            U::nameAttrs(q_str);

            q_str+=" FROM "+table
                +" INNER JOIN "+T::table+" ON ( "
                +bdd_used->escapeColum(table)+"."+bdd_used->escapeColum(_owner)+bdd_used->operators.at("exact")+T::table+".id), "
                +U::table
                +" WHERE ("
                +bdd_used->escapeColum(table)+"."+bdd_used->escapeColum(_owner)+bdd_used->operators.at("exact")+std::to_string(owner.pk)
                +" AND "
                +bdd_used->escapeColum(table)+"."+bdd_used->escapeColum(_linked)+bdd_used->operators.at("exact")+U::table+".id"
                +")";
            Query* q = bdd_used->query(q_str);
            linked.clear();
            q->getObj(linked);
            delete q;
        }
        return linked;
    }*/

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
