namespace orm
{
    template<typename T>
    Cache<T>::Cache()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Register] Cache of "<<T::table<<BLANC<<std::endl;
        #endif
    };

    template<typename T>
    Cache<T>::~Cache()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Delete] Cache of "<<T::table<<BLANC<<std::endl;
        #endif
    }

    template<typename T>
    typename Cache<T>::type_ptr Cache<T>::getOrCreate(const unsigned int& pk,DB& db,int max_depth)
    {
        //std::lock_guard<std::mutex> lock(_mutex);//lock
        //already existe
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;

        T* ptr = T::_get_ptr(pk,db,max_depth);
        if(ptr == nullptr)
            ptr = new T();
            
        map[pk].reset(ptr);
        return map[pk];
    }
    
    template<typename T>
    typename Cache<T>::type_ptr Cache<T>::getOrCreate(const unsigned int& pk,const Query& query,int& prefix,int max_depth)
    {
        const auto& res= map.find(pk);
        if(res != map.end())
        {
            T::incDepth(prefix,max_depth);
            return res->second;
        }
        type_ptr& r= map[pk];
        r.reset(T::createFromDB(query,prefix,max_depth));
        return r;
    }

    template<typename T>
    typename Cache<T>::type_ptr Cache<T>::getOrCreate(const Query& query,int max_depth)
    {
        int pk = -1;
        int index = query.db.getInitialGetcolumnNumber();
        query.get(pk,index);
        
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        type_ptr& r= map[pk];
        r.reset(T::createFromDB(query,--index,max_depth));
        return r;
    }



    template<typename T>
    void Cache<T>::__print__()
    {
        for(auto& i : map)
            std::cerr<<*i.second<<std::endl;
    }

/////////////////// PRIVATE ////////////////////

    template<typename T>
    typename Cache<T>::type_ptr& Cache<T>::add(typename Cache<T>::type_ptr& obj)
    {
        const auto& res=map.find(obj->pk);
        if(res != map.end())
        {
            return res->second;
        }
        map[obj->pk] = obj;
        return obj;
    }


    template<typename T>
    typename Cache<T>::type_ptr& Cache<T>::add(T& obj)
    {
        const auto& res=map.find(obj.pk);
        if(res != map.end())
        {
            return res->second;
        }
        type_ptr& r = map[obj.pk];
        r.reset(&obj);
        return r;
    }

    template<typename T>
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
    }


    template<typename T>
    void Cache<T>::clear(bool reset_pk)
    {
        if(reset_pk)
        {
            for(auto& i : map)
                i.second->pk = -1;
                
        }
        map.clear();
    }


    template<typename T>
    void Cache<T>::del(const unsigned int& pk)
    {
        map.erase(pk);
    }


}
