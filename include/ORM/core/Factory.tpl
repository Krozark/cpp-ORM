namespace orm
{

    template<typename T>
    T Factory<T>::create(const std::string& className) const
    {
        T res = nullptr;
        auto it = _constructors.find(className);
        if (it != _constructors.end())
        {
            res = it->second();
        }

        return res;
    }

    template<typename T>
    void Factory<T>::add(const std::string& className, std::function<T()> constructor)
    {
        _constructors.emplace(className, constructor);
    }

    template<typename T>
    typename Factory<T>::Container::const_iterator Factory<T>::begin() const
    {
        return _constructors.begin();
    }

    template<typename T>
    typename Factory<T>::Container::const_iterator Factory<T>::end() const
    {
        return _constructors.end();
    }

}
