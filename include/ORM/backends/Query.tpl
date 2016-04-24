namespace orm
{
    template<typename T>
    int Query::_getObj(T& obj,int max_depth)
    {
        if(not _executed)
        {
            _execute();
        }

        if (_next())
        {
            return obj.loadFromDB(*this,max_depth);
        }

        ORM_PRINT_WARNING("Query::getObj(T& obj,int max_depth) failed : No raw return")
        return 0;
    };

    template<typename T>
    int Query::_getObj(std::vector<std::shared_ptr<T>>& objs,int max_depth)
    {
        if(not _executed)
        {
            _execute();
        }
        int res = 0;

        while(_next())
        {
            auto tmp = T::cache.getOrCreate(*this,max_depth);
            //TODO
            //if(tmp)
            {
                objs.emplace_back(tmp);
                ++res;
            }
        }
        return res;
    };
};
