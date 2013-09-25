namespace orm
{
    template<typename T>
    int Query::getObj(T& obj,int max_depth)
    {
        if(not executed)
            execute();
        
        if (next())
            return obj.loadFromBdd(*this,max_depth);
        #if (ORM_DEBUG & ORM_DEBUG_GET_OBJ) || (ORM_VERBOSITY | ORM_WARNING)
        std::cerr<<JAUNE<<"[WARNING] Query::getObj(T& obj,int max_depth) failed : No raw return"<<BLANC<<std::endl;
        #endif
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
            objs.emplace_back(T::cache.getOrCreate(*this,max_depth));
            /*T* tmp = T::createFromBdd(*this,"",max_depth);
            if (tmp)
            {
                objs.emplace_back(T::cache.getOrCreate(tmp));
            }*/
            ++res;
        }   
        return res;     
    };
};
