#include <algorithm>    // std::swap

namespace orm
{
    template<typename T>
    QuerySet<T>::QuerySet(): limit_min(-1), limit_max(-1)
    {
    }

    template<typename T>
    QuerySet<T>::QuerySet(QuerySet&& tmp)
    {
        std::swap(filters,tmp.filters);
        std::swap(excludes,tmp.excludes);
        std::swap(order_by,tmp.order_by);
        limit_min = tmp.limit_min;
        limit_max = tmp.limit_max;
    }

    template<typename T>
    template<typename U,typename ... Args>
    QuerySet<T>& QuerySet<T>::filter(const U& value,const std::string& operande,const std::string& colum,const Args& ... args)
    {
        filters.emplace_back(Filter(makeColumName(T::table,colum,args ...),operande,value));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::filter(const std::list<Filter>& filter_list)
    {
        for(Filter& filter : filter_list)
            filters.emplace_back(filter);
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::filter(std::list<Filter>&& filter_list)
    {
        std::move_backward(filter_list.begin(), filter_list.end(), filters.end());
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(const std::string& colum)
    {
        order_by.emplace_back(colum);
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(std::string&& colum)
    {
        order_by.push_back(colum);
        return *this;
    }

    template<typename T>
    template<typename U,typename ... Args>
    QuerySet<T>& QuerySet<T>::exclude(const U& value,const std::string& operande,const std::string& colum,const Args& ... args)
    {
        excludes.emplace_back(Filter(makeColumName(T::table,colum,args ...),operande,value));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::exclude(const std::list<Filter>& exclude_list)
    {
        for(Filter& filter : exclude_list)
            excludes.emplace_back(filter);
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::exclude(std::list<Filter>&& exclude_list)
    {
        std::move_backward(exclude_list.begin(), exclude_list.end(), excludes.end());
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::limit(const unsigned int& max)
    {
        limit_max = static_cast<int>(max);
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::limit(const unsigned int& min,const unsigned int& max)
    {
        limit_min = static_cast<int>(min);
        limit_max = static_cast<int>(max);
    }

    /*template<typename T>
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
    }*/

    template<typename T>
    void QuerySet<T>::__print__() const
    {
        std::cout<<"Filter: ";
        for (auto& u :  filters)
            u.__print__();
    };

    template<typename T>
    template<typename ... Args>
    std::string QuerySet<T>::makeColumName(const std::string& prefix,const std::string& colum,Args&& ...args)
    {
        return makeColumName(JOIN_ALIAS(prefix,colum),args...);
    }

    template<typename T>
    template<typename ... Args>
    std::string QuerySet<T>::makeColumName(std::string&& prefix,std::string&& colum,Args&& ...args)
    {
        return makeColumName(JOIN_ALIAS(prefix,colum),args ...);
    }

    template<typename T>
    std::string QuerySet<T>::makeColumName(std::string colum)
    {
        return colum;
    }
}
