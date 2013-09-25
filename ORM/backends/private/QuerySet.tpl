#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

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
    QuerySet<T>& QuerySet<T>::filter(const U& value,const std::string& operande,const std::string& column,const Args& ... args)
    {
        filters.emplace_back(new Filter<U>(makecolumname(T::table,column,args ...),operande,value));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(const std::string& column,const char order)
    {
        if( order == '-')
            order_by.push_back(makecolumname(T::table,column)+" DESC");
        else
            order_by.push_back(makecolumname(T::table,column)+" ASC");
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(std::string&& column,const char order)
    {
        if( order == '-')
            order_by.push_back(makecolumname(T::table,column)+" DESC");
        else
            order_by.push_back(makecolumname(T::table,column)+" ASC");
        return *this;
    }

    template<typename T>
    template<typename U,typename ... Args>
    QuerySet<T>& QuerySet<T>::exclude(const U& value,const std::string& operande,const std::string& column,const Args& ... args)
    {
        excludes.emplace_back(new Filter<U>(makecolumname(T::table,column,args ...),operande,value));
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
        if(limit_count <= 0)
            limit_count = 1;

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
        for (auto* u :  filters)
            u->__print__();
        std::cout<<"exclude: ";
        for (auto* u :  excludes)
            u->__print__();
        std::cout<<"order_by: ";
        for (auto& u :  order_by)
            std::cout<<u<<" ";
        std::cout<<std::endl<<"limit:<"<<limit_skip<<","<<limit_count<<">"<<std::endl;
    };

    template<typename T>
    template<typename ... Args>
    std::string QuerySet<T>::makecolumname(const std::string& prefix,const std::string& column,Args&& ...args)
    {
        return makecolumname(JOIN_ALIAS(prefix,column),args...);
    }

    template<typename T>
    std::string QuerySet<T>::makecolumname(const std::string& prefix,const std::string& column)
    {
        return T::bdd_used->escapecolumn(prefix)+"."+T::bdd_used->escapecolumn(column);
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
            /// \todo change column alias for complet name

            if(filters_size > 0)
            {
                auto begin = filters.begin();
                const auto& end = filters.end();

                q_str+= (*begin)->column
                    +T::bdd_used->formatPreparedValue((*begin)->ope);

                while(++begin != end)
                {
                    q_str+=" AND "
                        +(*begin)->column
                        +T::bdd_used->formatPreparedValue((*begin)->ope);
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

                q_str+= (*begin)->column
                    +T::bdd_used->formatPreparedValue((*begin)->ope);

                while(++begin != end)
                {
                    q_str+=" AND "
                        +(*begin)->column
                        +T::bdd_used->formatPreparedValue((*begin)->ope);
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

        Query* q = T::bdd_used->prepareQuery(q_str);

        {//bind values
            unsigned int index = 1;
            if(filters_size > 0)
            {
                auto begin = filters.begin();
                const auto& end = filters.end();
                while(begin != end)
                {

                    (*begin)->set(q,index);
                    ++begin;
                    ++index;
                    //q->set(T::bdd_used->formatValue(begin->ope,begin->value),index++);
                }
            }
            if(excludes_size >0)
            {
                auto begin = excludes.begin();
                const auto& end = excludes.end();
                while(begin != end)
                {
                    (*begin)->set(q,index);
                    ++begin;
                    ++index;
                    //q->set(T::bdd_used->formatValue(begin->ope,begin->value),index++);
                }
            }
        }
        
        return q;
    }
}
