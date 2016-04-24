namespace orm
{
    template<typename T>
    Cache<T>::Cache()
    {
        #ifdef ORM_USE_CACHE
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Register] Cache of "<<SqlObject<T>::table<<BLANC<<std::endl;
        #endif
        #endif
    };

    template<typename T>
    Cache<T>::~Cache()
    {
        #ifdef ORM_USE_CACHE
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Delete] Cache of "<<SqlObject<T>::table<<BLANC<<std::endl;
        #endif
        #endif
    }

    template<typename T>
    typename Cache<T>::pointer Cache<T>::getOrCreate(const unsigned int& pk,DB& db,int max_depth)
    {
        //std::lock_guard<std::mutex> lock(_mutex);//lock
        //already existe
        #ifdef ORM_USE_CACHE
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        #endif

        pointer ptr = T::_get_ptr(pk,db,max_depth);
        if(ptr.get() == nullptr)
            ptr = T::create();

        #ifdef ORM_USE_CACHE
        map[pk] = ptr;
        return map[pk];
        #else
        return pointer(ptr);
        #endif
    }

    template<typename T>
    typename Cache<T>::pointer Cache<T>::getOrCreate(const unsigned int& pk,const Query& query,int& prefix,int max_depth)
    {
        #ifdef ORM_USE_CACHE
        const auto& res= map.find(pk);
        if(res != map.end())
        {
            T::incDepth(prefix,max_depth);
            return res->second;
        }
        pointer& r= map[pk];
        r = T::createFromDB(query,prefix,max_depth);
        #else
        pointer r = T::createFromDB(query,prefix,max_depth);
        #endif
        return r;
    }

    template<typename T>
    typename Cache<T>::pointer Cache<T>::getOrCreate(const Query& query,int max_depth)
    {
        int pk = -1;
        int index = query._db._getInitialGetcolumnNumber();
        query._get(pk,index);

        #ifdef ORM_USE_CACHE
        const auto& res= map.find(pk);

        if(res != map.end())
            return res->second;

        pointer& r= map[pk];
        r = SqlObject<T>::createFromDB(query,--index,max_depth);

        #else
        pointer r = SqlObject<T>::createFromDB(query,--index,max_depth);
        #endif
        return r;
    }



    template<typename T>
    void Cache<T>::debugPrint()
    {
        #ifdef ORM_USE_CACHE
        for(auto& i : map)
            std::cerr<<*static_cast<SqlObject<T>*>(i.second.get())<<std::endl;
        #endif
    }

    template<typename T>
    void Cache<T>::clear(bool reset_pk)
    {
        #ifdef ORM_USE_CACHE
        if(reset_pk)
        {
            for(auto& i : map)
                i.second->SqlObject<T>::pk = -1;

        }
        map.clear();
        #endif
    }

/////////////////// PRIVATE ////////////////////

    template<typename T>
    typename Cache<T>::pointer& Cache<T>::add(typename Cache<T>::pointer& obj)
    {
        #ifdef ORM_USE_CACHE
        auto pk = obj.get()->SqlObject<T>::pk;
        const auto& res=map.find(pk);
        if(res != map.end())
        {
            return res->second;
        }
        map[pk] = obj;
        #endif
        return obj;
    }

    template<typename T>
    void Cache<T>::del(const unsigned int& pk)
    {
        #ifdef ORM_USE_CACHE
        map.erase(pk);
        #endif
    }


}
