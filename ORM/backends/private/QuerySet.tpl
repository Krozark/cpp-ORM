namespace orm
{
    template<typename T>
    QuerySet<T>::QuerySet()
    {
    }

    template<typename T>
    template<typename U>
    QuerySet<T>& QuerySet<T>::filter(const std::string& colum,const std::string operande, const U& value)
    {
        std::cerr<<"[TODO]: QuerySet<T>::filter()"<<std::endl;
        return *this;
    };

    template<typename T>
    template<typename U,typename ... Args>
    QuerySet<T>& QuerySet<T>::filter(Filter<U>&& filter,Args&& ... args)
    {
        std::cerr<<"[TODO]: QuerySet<T>::filter()"<<std::endl;
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(const std::string& colum)
    {
        std::cerr<<"[TODO]: QuerySet<T>::orderBy()"<<std::endl;
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet::exclude()
    {
        std::cerr<<"[todo]: queryset<t>::exclude()"<<std::endl;
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::agregate()
    {
        std::cerr<<"[todo]: queryset<t>::agregate()"<<std::endl;
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::limite(int max)
    {
        std::cerr<<"[todo]: queryset<t>::limite(int)"<<std::endl;
        return *this;
    }
    
    template<typename T>
    QuerySet<T>& QuerySet<T>::limite(int min,int max)
    {
        std::cerr<<"[todo]: queryset<t>::limite(int,int)"<<std::endl;
        return *this;
    }

    template<typename T>
    T QuerySet<T>::get()
    {
        std::cerr<<"[todo]: queryset<t>::get()"<<std::endl;
        return T();
    }

    template<typename T>
    bool QuerySet<T>::get(T& obj)
    {
        std::cerr<<"[todo]: queryset<t>::get(T& obj)"<<std::endl;
        return false;
    }

    template<typename T>
    bool QuerySet<T>::get(typename std::list<Cache<T>::type_ptr>& objs);
    {
        std::cerr<<"[todo]: queryset<t>::get(Cache<T>::type_ptr&)"<<std::endl;
        return T();
    }
}
