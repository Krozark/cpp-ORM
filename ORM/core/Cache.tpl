namespace orm
{
    template<typename T>
    std::shared_ptr<T>& Cache<T>::getOrCreate(const unsigned int& pk)
    {
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        map[pk].reset(T::_get_ptr(pk));
        return map[pk];
    }

    template<typename T>
    std::shared_ptr<T>& Cache<T>::getOrCreate(const unsigned int& pk,const Query& query)
    {
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        std::shared_ptr<T>& r= map[pk];
        //= T::createFromBdd(query);
        //r->loadFromBdd(query);
        r.reset(T::createFromBdd(query));
        return r;
    }

    template<typename T>
    std::shared_ptr<T>& Cache<T>::getOrCreate(T* tmp)
    {
        const auto& res=map.find(tmp->pk);
        if(res != map.end())
        {
            delete tmp;
            return res->second;
        }
        std::shared_ptr<T>& r = map[tmp->pk];
        r.reset(tmp);
        return r;
    }

    template<typename T>
    void Cache<T>::__print__()
    {
        for(auto& i : map)
            std::cout<<*i.second<<std::endl;
    }
}
