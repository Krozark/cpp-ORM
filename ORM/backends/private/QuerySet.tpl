#include <algorithm>    // std::swap

namespace orm
{
    template<typename T>
    QuerySet<T>::QuerySet(): limit_skip(0), limit_count(-1)
    {
    }

    template<typename T>
    QuerySet<T>::QuerySet(QuerySet&& tmp)
    {
        std::swap(filters,tmp.filters);
        std::swap(excludes,tmp.excludes);
        std::swap(order_by,tmp.order_by);
        limit_skip = tmp.limit_skip;
        limit_count = tmp.limit_count;
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
        for(const Filter& filter : filter_list)
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
    QuerySet<T>& QuerySet<T>::orderBy(const std::string& colum,const char order)
    {
        if( order == '-')
            order_by.push_back(makeColumName(T::table,colum)+" DESC");
        else
            order_by.push_back(makeColumName(T::table,colum)+" ASC");
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(std::string&& colum,const char order)
    {
        if( order == '-')
            order_by.push_back(makeColumName(T::table,colum)+" DESC");
        else
            order_by.push_back(makeColumName(T::table,colum)+" ASC");
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
    QuerySet<T>& QuerySet<T>::limit(const unsigned int& count)
    {
        limit_count = static_cast<int>(count);
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::limit(const unsigned int& skip,const unsigned int& count)
    {
        limit_skip = static_cast<int>(skip);
        limit_count = static_cast<int>(count);
    }

    /***
    * \todo make query like:
    * SELECT SUM(`sort`.`niveau_max`) AS `niveau_max__sum` FROM `sort` WHERE (...)
    * SELECT AVG(`website_sort`.`niveau_max`) AS `niveau_max__avg`, SUM(`website_sort`.`niveau_max`) AS `niveau_max__sum` FROM `website_sort` WHERE (`website_sort`.`passif` = 0  AND `website_sort`.`niveau_max` >= 2 )
    * AVG, SUM, MIN, MAX
    **/
    /*template<typename T>
    QuerySet<T>& QuerySet<T>::aggregate()
    {
        std::cerr<<"[todo]: queryset<t>::agregate()"<<std::endl;
        return *this;
    };*/

    template<typename T>
    bool QuerySet<T>::get(T& obj,int max_depth)
    {
        Query* q = makeQuery(max_depth);
        bool res = q->getObj(obj,max_depth);
        delete q;
        return res;
    }

    template<typename T>
    int QuerySet<T>::get(typename std::list<std::shared_ptr<T>>& objs,int max_depth)
    {
        Query* q = makeQuery(max_depth);
        int res = q->getObj(objs,max_depth);
        delete q;
        return res;
    }

    template<typename T>
    void QuerySet<T>::__print__() const
    {
        std::cout<<"Filter: ";
        for (auto& u :  filters)
            u.__print__();
        std::cout<<"exclude: ";
        for (auto& u :  excludes)
            u.__print__();
        std::cout<<"order_by: ";
        for (auto& u :  order_by)
            std::cout<<u<<" ";
        std::cout<<std::endl<<"limit:<"<<limit_skip<<","<<limit_count<<">"<<std::endl;


    };

    template<typename T>
    template<typename ... Args>
    std::string QuerySet<T>::makeColumName(const std::string& prefix,const std::string& colum,Args&& ...args)
    {
        return makeColumName(JOIN_ALIAS(prefix,colum),args...);
    }

    /*template<typename T>
    template<typename ... Args>
    std::string QuerySet<T>::makeColumName(std::string&& prefix,std::string&& colum,Args&& ...args)
    {
        return makeColumName(JOIN_ALIAS(prefix,colum),args ...);
    }*/

    template<typename T>
    std::string QuerySet<T>::makeColumName(const std::string& prefix,const std::string& colum)
    {
        return T::bdd_used->escapeColum(prefix)+"."+T::bdd_used->escapeColum(colum);
    }

    template<typename T>
    Query* QuerySet<T>::makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        T::nameAttrs(q_str,T::table,max_depth);

        q_str+="\nFROM ";
        T::nameTables(q_str,"",max_depth);

        const int filters_size = filters.size();
        const int excludes_size = excludes.size();

        {//filters and excludes


            if(filters_size > 0 or excludes_size >0)
                q_str+=" \nWHERE (";
            /// \todo change colum alias for complet name

            if(filters_size > 0)
            {
                auto begin = filters.begin();
                const auto& end = filters.end();

                /*q_str+= begin->colum
                    +T::bdd_used->escapeValue(begin->ope,begin->value);

                while(++begin != end)
                {
                    q_str+=" AND "
                        +begin->colum
                        +T::bdd_used->escapeValue(begin->ope,begin->value);
                }*/

                q_str+= begin->colum
                    +T::bdd_used->escapeValue(begin->ope,"(?)");

                while(++begin != end)
                {
                    q_str+=" AND "
                        +begin->colum
                        +T::bdd_used->escapeValue(begin->ope,"(?)");
                }
            }

            if(excludes_size >0)
            {
                if(filters_size >0)
                    q_str+=" AND NOT (";
                else
                    q_str+="NOT (";

                auto begin = excludes.begin();
                const auto& end = excludes.end();

                /*q_str+= begin->colum
                    +T::bdd_used->escapeValue(begin->ope,begin->value);

                while(++begin != end)
                {
                    q_str+=" AND "
                        +begin->colum
                        +T::bdd_used->escapeValue(begin->ope,begin->value);
                }*/

                q_str+= begin->colum
                    +T::bdd_used->escapeValue(begin->ope,"(?)");

                while(++begin != end)
                {
                    q_str+=" AND "
                        +begin->colum
                        +T::bdd_used->escapeValue(begin->ope,"(?)");
                }

                q_str+=") ";
            }

            if(filters_size > 0 or excludes_size > 0)
                q_str+=") ";
        }
        
        int _size = order_by.size();
        if(_size >0)
        {
            q_str+=" ORDER BY ";
            auto begin = order_by.begin();
            const auto& end = order_by.end();
            q_str+= (*begin);

            while(++begin != end)
            {
                q_str+=" ,"+(*begin);
            }

        }

        if(limit_count > 0)
            q_str+= T::bdd_used->limit(limit_skip,limit_count);

        std::cout<<q_str<<std::endl;

        Query* q = T::bdd_used->prepareQuery(q_str);

        {//bind values
            int index = 1;
            if(filters_size > 0)
            {
                auto begin = filters.begin();
                const auto& end = filters.end();
                while(begin != end)
                {
                    std::cout<<begin->value<<std::endl;
                    q->set(begin->value,index++);
                    ++begin;
                }
            }
            if(excludes_size >0)
            {
                auto begin = excludes.begin();
                const auto& end = excludes.end();
                while(begin != end)
                {
                    q->set(begin->value,index++);
                    ++begin;
                }
            }
        }
        
        return q;
    }
}
