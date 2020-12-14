#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template<typename T>
    QuerySet<T>::QuerySet(DB& db):
        _limitSkip(0),
        _limitCount(-1),
        _db(db)
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
        _filters.emplace_back(Q<T>(std::forward<Args>(args)...));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::filter(const FilterSet<T>& f)
    {
        _filters.emplace_back(f);
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::filter(FilterSet<T>&& f)
    {
        _filters.push_back(std::move(f));
        return *this;
    }

    template<typename T>
    template<typename ... Args>
    QuerySet<T>& QuerySet<T>::exclude(Args&& ... args)
    {
        _filters.push_back(not Q<T>(std::forward<Args>(args)...));
        return *this;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::exclude(const FilterSet<T>& f)
    {
        _filters.emplace_back(not f);
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::exclude(FilterSet<T>&& f)
    {
        _filters.push_back(std::move(operator!(std::forward<FilterSet<T>>(f))));
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(const std::string& column,const char order)
    {
        if(column == "?")
        {
            _orderBy.push_back(T::staticGetDefaultDataBase()._operators.at("?"));
        }
        else if( order == '-')
        {
            _orderBy.push_back(DB::_makecolumname(T::staticGetDefaultDataBase(),T::_table,column)+" DESC");
        }
        else
        {
            _orderBy.push_back(DB::_makecolumname(T::staticGetDefaultDataBase(),T::_table,column)+" ASC");
        }
        return *this;
    }

    template<typename T>
    QuerySet<T>& QuerySet<T>::orderBy(std::string&& column,const char order)
    {
        if(column == "?")
        {
            _orderBy.push_back(T::staticGetDefaultDataBase().operators.at("?"));
        }
        else if( order == '-')
        {
            _orderBy.push_back(DB::_makecolumname(T::staticGetDefaultDataBase(),T::_table,column)+" DESC");
        }
        else
        {
            _orderBy.push_back(DB::_makecolumname(T::staticGetDefaultDataBase(),T::_table,column)+" ASC");
        }
        return *this;
    }


    template<typename T>
    QuerySet<T>& QuerySet<T>::limit(const int& count)
    {
        _limitCount = count;
    };

    template<typename T>
    QuerySet<T>& QuerySet<T>::limit(const int& skip,const int& count)
    {
        _limitSkip = skip;
        _limitCount = count;
    }


    template<typename T>
    bool QuerySet<T>::get(T& obj,int max_depth)
    {
        if(_limitCount <= 0)
        {
            _limitCount = 1;
        }

        std::shared_ptr<Query> q = _makeQuery(max_depth);
        bool res = q->_getObj(obj,max_depth);
        return res;
    }

    template<typename T>
    int QuerySet<T>::get(typename QuerySet<T>::pointer_array& objs,int max_depth)
    {
        std::shared_ptr<Query> q = _makeQuery(max_depth);
        int res = q->_getObj(objs,max_depth);
        return res;
    }

    template<typename T>
    void QuerySet<T>::debugPrint() const
    {
        std::string q_str ="SELECT ";
        T::_staticNameAttrs(q_str,T::_table,ORM_DEFAULT_MAX_DEPTH,_db);

        q_str+="\nFROM ";
        T::_staticNameTables(q_str,"",ORM_DEFAULT_MAX_DEPTH,_db);

        const int filters_size = _filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";

            auto begin = _filters.begin();
            const auto& end = _filters.end();

            std::cout<<q_str;
            q_str.clear();
            begin->debugPrint(T::staticGetDefaultDataBase());

            while(++begin != end)
            {
                std::cout<<" AND ";
                begin->debugPrint(T::staticGetDefaultDataBase());
            }

            std::cout<<") ";
        }

        int _size = _orderBy.size();
        if(_size >0)
        {
            std::cout<<" ORDER BY ";
            auto begin = _orderBy.begin();
            const auto& end = _orderBy.end();
            std::cout<<(*begin);

            while(++begin != end)
            {
                std::cout<<" ,"+(*begin);
            }

        }
        if(_limitCount > 0)
        {
            std::cout<<_db._limit(_limitSkip,_limitCount);
        }
        std::cout<<std::endl;
    };


    template<typename T>
    std::shared_ptr<Query> QuerySet<T>::_makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        SqlObject<T>::_staticNameAttrs(q_str,SqlObject<T>::_table,max_depth,_db);

        q_str+="\nFROM ";
        SqlObject<T>::_staticNameTables(q_str,"",max_depth,_db);

        const int filters_size = _filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";

            auto begin = _filters.begin();
            const auto& end = _filters.end();

            begin->_toQuery(q_str,_db);

            while(++begin != end)
            {
                q_str+=" AND ";
                begin->_toQuery(q_str,_db);
            }

            q_str+=") ";
        }

        int _size = _orderBy.size();
        if(_size >0)
        {
            q_str+=" ORDER BY ";
            auto begin = _orderBy.begin();
            const auto& end = _orderBy.end();
            q_str+= (*begin);

            while(++begin != end)
            {
                q_str+=" ,"+(*begin);
            }

        }

        if(_limitCount > 0)
        {
            q_str+= _db._limit(_limitSkip,_limitCount);
        }

        std::shared_ptr<Query> q = _db.prepareQuery(q_str);
        if(filters_size > 0)
        {
            auto begin = _filters.begin();
            const auto& end = _filters.end();
            unsigned int index = _db._getInitialSetcolumnNumber();
            while(begin != end)
            {

                begin->_set(*q,index);
                ++begin;
                ++index;
            }
        }

        return q;
    }
}
