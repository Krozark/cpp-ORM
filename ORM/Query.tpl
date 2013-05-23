namespace orm
{
    template<typename T>
    int Query::getObj(T& obj)
    {
        if(not executed)
            execute();
        
        if (next())
            return obj.loadFromBdd(*this);
        return 0;
    };

    template<typename T>
    int Query::getObj(std::list<T*>& objs)
    {
        if(not executed)
            execute();
        int res = 0;
        while(next())
        {
            T* tmp = T::createFromBdd(*this);
            if (tmp)
                objs.emplace_back(tmp);
            ++res;
        }   
        return res;     
    };
};
