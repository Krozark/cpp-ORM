namespace orm
{
    template<typename T>
    std::shared_ptr<T>& Cache::getOrCreate(const int& pk)
    {
        auto res&= map.at(pk);
        if(res != map.end())
            return res->get();
        return (map[pk] = T::get(pk,false)).get();
    }
}
