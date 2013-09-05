namespace orm
{
    //TODO tester le retour de _get_ptr qui peut être 0
    template<typename T>
    typename Cache<T>::type_ptr& Cache<T>::getOrCreate(const unsigned int& pk,int max_depth)
    {
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        map[pk].reset(T::_get_ptr(pk,max_depth));
        return map[pk];
    }
    
    //TODO add to creatoFromBdd depth
    template<typename T>
    typename Cache<T>::type_ptr& Cache<T>::getOrCreate(const unsigned int& pk,const Query& query)
    {
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        type_ptr& r= map[pk];
        //= T::createFromBdd(query);
        //r->loadFromBdd(query);
        r.reset(T::createFromBdd(query));
        return r;
    }

    /*template<typename T>
    typename Cache<T>::type_ptr& Cache<T>::getOrCreate(T* tmp)
    {
        const auto& res=map.find(tmp->pk);
        if(res != map.end())
        {
            delete tmp;
            return res->second;
        }
        type_ptr& r = map[tmp->pk];
        r.reset(tmp);
        return r;
    }*/

    template<typename T>
    void Cache<T>::del(const int& pk)
    {
        map.erase(pk);
    }


    template<typename T>
    void Cache<T>::__print__()
    {
        for(auto& i : map)
            std::cout<<*i.second<<std::endl;
    }
}
