#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template<typename T>
    QuerySet<T>::QuerySet(Bdd& db): limit_skip(0), limit_count(-1), bdd(db)
    {
        
    }

    template<typename T>
    QuerySet<T>::~QuerySet()
    {
    }


    template<typename T>
    template<typename ... Args>
    QuerySet<T>& QuerySet<T>::filter(Args&& ... args)
    {
        filters.emplace_back(Q<T>(std::forward<Args>(args)...));
        //Bdd::makecolumname(*T::default_connection,T::table,column,args ...),operande,value));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::filter(const FilterSet& f)
    {
        filters.emplace_back(f);
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::filter(FilterSet&& f)
    {
        filters.push_back(std::move(f));
        return *this;
    }

    template<typename T>
    template<typename ... Args>
    QuerySet<T>& QuerySet<T>::exclude(Args&& ... args)
    {
        filters.push_back(not Q<T>(std::forward<Args>(args)...));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::exclude(const FilterSet& f)
    {
        filters.emplace_back(not f);
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::exclude(FilterSet&& f)
    {
        filters.push_back(std::move(operator!(std::forward<FilterSet>(f))));
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(const std::string& column,const char order)
    {
        if(column == "?")
            order_by.push_back(T::default_connection->operators.at("?"));
        else if( order == '-')
            order_by.push_back(Bdd::makecolumname(*T::default_connection,T::table,column)+" DESC");
        else
            order_by.push_back(Bdd::makecolumname(*T::default_connection,T::table,column)+" ASC");
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(std::string&& column,const char order)
    {
        if(column == "?")
            order_by.push_back(T::default_connection->operators.at("?"));
        else if( order == '-')
            order_by.push_back(Bdd::makecolumname(*T::default_connection,T::table,column)+" DESC");
        else
            order_by.push_back(Bdd::makecolumname(*T::default_connection,T::table,column)+" ASC");
        return *this;
    }


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
        std::string q_str ="SELECT ";
        T::nameAttrs(q_str,T::table,ORM_DEFAULT_MAX_DEPTH,bdd);

        q_str+="\nFROM ";
        T::nameTables(q_str,"",ORM_DEFAULT_MAX_DEPTH,bdd);

        const int filters_size = filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";

            auto begin = filters.begin();
            const auto& end = filters.end();

            std::cout<<q_str;
            q_str.clear();
            begin->__print__(*T::default_connection);

            while(++begin != end)
            {
                std::cout<<" AND ";
                begin->__print__(*T::default_connection);
            }

            std::cout<<") ";
        }
        
        int _size = order_by.size();
        if(_size >0)
        {
            std::cout<<" ORDER BY ";
            auto begin = order_by.begin();
            const auto& end = order_by.end();
            std::cout<<(*begin);

            while(++begin != end)
            {
                std::cout<<" ,"+(*begin);
            }

        }
        if(limit_count > 0)
            std::cout<<bdd.limit(limit_skip,limit_count);
        std::cout<<std::endl;
    };


    template<typename T>
    Query* QuerySet<T>::makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        T::nameAttrs(q_str,T::table,max_depth,bdd);

        q_str+="\nFROM ";
        T::nameTables(q_str,"",max_depth,bdd);

        const int filters_size = filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";

            auto begin = filters.begin();
            const auto& end = filters.end();

            begin->toQuery(q_str,bdd);

            while(++begin != end)
            {
                q_str+=" AND ";
                begin->toQuery(q_str,bdd);
            }

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
            q_str+= bdd.limit(limit_skip,limit_count);

        Query* q = bdd.prepareQuery(q_str);

        unsigned int index = bdd.getInitialGetcolumnNumber();
        if(filters_size > 0)
        {
            auto begin = filters.begin();
            const auto& end = filters.end();
            while(begin != end)
            {

                begin->set(q,index);
                ++begin;
                ++index;
            }
        }
        
        return q;
    }
}
