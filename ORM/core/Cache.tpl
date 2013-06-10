namespace orm
{
    template<typename T>
    std::shared_ptr<SQLObjectBase>& Cache::getOrCreate(const int& pk)
    {
        std::string key(T::table+"."+std::to_string(pk));
        auto res&= map.at(key);
        if(res != map.end())
            return res;
        return map[key] = T::get(pk);
    }
}
