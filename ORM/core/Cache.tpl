namespace orm
{
    template<typename T>
    std::shared_ptr<T>& Cache<T>::getOrCreate(const unsigned int& pk)
    {
        auto res= map.find(pk);
        if(res != map.end())
            return res->second;
        map[pk].reset(T::_get_ptr(pk));
        return map[pk];
    }
}
