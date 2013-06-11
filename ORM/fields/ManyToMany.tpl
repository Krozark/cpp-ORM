namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner)
    {
    }

    template<typename T,typename U>
    std::list<std::shared_ptr<U> >& ManyToMany<T,U>::all(bool maj)
    {
        if(maj)
        {
            /*select * 
             from perso_spell,perso,spell
             WHERE (
             perso.id = perso_spell.perso_id
             AND spell.id = perso_spell.spell_id
             );*/
            std::string q_str="SELECT "
                //owner (juste pk)
                +bdd_used->escape_colum(T::table)+"."+bdd_used->escape_colum("id")+" AS "+bdd_used->escape_value(T::table+".id");
            q_str+=", ";
            //linked(all)
            U::nameAttrs(q_str);

            q_str+=" FROM "+table+", "+T::table+", "+U::table
                +" WHERE ("
                +bdd_used->escape_colum(table)+"."+bdd_used->escape_colum(_owner)+bdd_used->operators.at("exact")+bdd_used->escape_value(T::table+".id")
                +" AND "
                +bdd_used->escape_colum(table)+"."+bdd_used->escape_colum(_linked)+bdd_used->operators.at("exact")+bdd_used->escape_value(U::table+".id")
                +")";

            Query* q = bdd_used->query(q_str);
            linked.clear();
            q->getObject(linked);
            delete q;
        }
        return linked;
    }
}
