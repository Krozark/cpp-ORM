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
            /* 
             Select T::nameAttr(q_str), U::nameAttr(q_str)
             from T.table, U::table
             where owner_id "exact" owner.pk
             */
        }
        return linked;
    }
}
