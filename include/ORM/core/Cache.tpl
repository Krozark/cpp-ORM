namespace orm
{
    template<typename T>
    Cache<T>::Cache()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_MAGENTA<<"[Register] Cache of "<<SqlObject<T>::table<<ORM_COLOUR_NONE<<std::endl;
        #endif
    };

    template<typename T>
    Cache<T>::~Cache()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_MAGENTA<<"[Delete] Cache of "<<SqlObject<T>::table<<ORM_COLOUR_NONE<<std::endl;
        #endif
    }

    template<typename T>
    typename Cache<T>::pointer Cache<T>::getOrCreate(const unsigned int& pk,DB& db,int max_depth)
    {
        //std::lock_guard<std::mutex> lock(_mutex);//lock
        //already existe
        const auto& res= _map.find(pk);
        if(res != _map.end())
        {
            return res->second;
        }

        pointer ptr = T::_get_ptr(pk,db,max_depth);
        if(ptr.get() == nullptr)
        {
            ptr = T::create();
        }

        _map[pk] = ptr;
        return _map[pk];
    }

    template<typename T>
    typename Cache<T>::pointer Cache<T>::getOrCreate(const unsigned int& pk,const Query& query,int& prefix,int max_depth)
    {
        const auto& res= _map.find(pk);
        if(res != _map.end())
        {
            T::_incDepth(prefix,max_depth);
            return res->second;
        }
        pointer& r= _map[pk];
        r = T::createFromDB(query,prefix,max_depth);

        return r;
    }

    template<typename T>
    typename Cache<T>::pointer Cache<T>::getOrCreate(const Query& query,int max_depth)
    {
        int pk = -1;
        int index = query._db._getInitialGetcolumnNumber();
        query._get(pk,index);

        const auto& res= _map.find(pk);

        if(res != _map.end())
        {
            return res->second;
        }

        pointer& r= _map[pk];
        r = SqlObject<T>::createFromDB(query,--index,max_depth);

        return r;
    }



    template<typename T>
    void Cache<T>::debugPrint()
    {
        for(auto& i : _map)
        {
            std::cerr<<*static_cast<SqlObject<T>*>(i.second.get())<<std::endl;
        }
    }

    template<typename T>
    void Cache<T>::clear(bool reset_pk)
    {
        if(reset_pk)
        {
            for(auto& i : _map)
            {
                i.second->SqlObject<T>::pk = -1;
            }

        }
        _map.clear();
    }

/////////////////// PRIVATE ////////////////////

    template<typename T>
    typename Cache<T>::pointer& Cache<T>::_add(typename Cache<T>::pointer& obj)
    {
        auto pk = obj.get()->SqlObject<T>::pk;
        const auto& res = _map.find(pk);
        if(res != _map.end())
        {
            return res->second;
        }

        _map[pk] = obj;

        return obj;
    }

    template<typename T>
    void Cache<T>::_del(const unsigned int& pk)
    {
        _map.erase(pk);
    }


}
