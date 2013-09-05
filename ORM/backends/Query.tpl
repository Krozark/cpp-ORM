namespace orm
{
    template<typename T>
    int Query::getObj(T& obj,int max_depth)
    {
        if(not executed)
            execute();
        
        if (next())
            return obj.loadFromBdd(*this);
        return 0;
    };

    template<typename T>
    int Query::getObj(std::list<std::shared_ptr<T> >& objs,int max_depth)
    {
        if(not executed)
            execute();
        int res = 0;
        while(next())
        {
            T* tmp = T::createFromBdd(*this);
            if (tmp)
            {
                objs.emplace_back(T::cache.getOrCreate(tmp));
            }
            ++res;
        }   
        return res;     
    };
};
