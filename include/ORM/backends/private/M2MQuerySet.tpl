#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>::M2MQuerySet(const ManyToMany<OWNER,RELATED>& m2m,DB& db):
        _limitSkip(0),
        _limitCount(-1),
        _db(db)
    {
        _filters.emplace_back(Q<ManyToMany<OWNER,RELATED>>(
            m2m._owner.pk,
            op::exact,
            ManyToMany<OWNER,RELATED>::ORM_MAKE_NAME(_owner)));
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>::~M2MQuerySet()
    {
    }


    template <typename OWNER, typename RELATED>
    template <typename T,typename ... Args>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(T&& v,const std::string& operand,Args&& ... args)
    {
        _filters.emplace_back(
            Q<ManyToMany<OWNER, RELATED>>(std::forward<T>(v),
            operand,
            ManyToMany<OWNER,RELATED>::ORM_MAKE_NAME(_linked), std::forward<Args>(args)...)
        );
        return *this;
    };

    template<typename OWNER,typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(const FilterSet<ManyToMany<OWNER,RELATED>>& f)
    {
        _filters.emplace_back(f);
        return *this;
    }

    template<typename OWNER,typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(FilterSet<ManyToMany<OWNER,RELATED>>&& f)
    {
        _filters.push_back(std::move(f));
        return *this;
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::orderBy(const std::string& column,const char order)
    {
        if( order == op::desc)
        {
            _orderBy.push_back(DB::_makecolumname(ManyToMany<OWNER,RELATED>::staticGetDefaultDataBase(),ManyToMany<OWNER,RELATED>::_related,column)+" DESC");
        }
        else
        {
            _orderBy.push_back(DB::_makecolumname(ManyToMany<OWNER,RELATED>::staticGetDefaultDataBase(),ManyToMany<OWNER,RELATED>::_related,column)+" ASC");
        }
        return *this;
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::orderBy(std::string&& column,const char order)
    {
        if( order == op::desc)
        {
            _orderBy.push_back(DB::_makecolumname(ManyToMany<OWNER,RELATED>::staticGetDefaultDataBase(),ManyToMany<OWNER,RELATED>::_related,column)+" DESC");
        }
        else
        {
            _orderBy.push_back(DB::_makecolumname(ManyToMany<OWNER,RELATED>::staticGetDefaultDataBase(),ManyToMany<OWNER,RELATED>::_related,column)+" ASC");
        }
        return *this;
    }


    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::limit(const unsigned int& count)
    {
        _limitCount = static_cast<int>(count);
        return *this;
    };

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::limit(const unsigned int& skip,const unsigned int& count)
    {
        _limitSkip = static_cast<int>(skip);
        _limitCount = static_cast<int>(count);
        return *this;
    }


    template <typename OWNER, typename RELATED>
    int M2MQuerySet<OWNER,RELATED>::get(typename RELATED::pointer_array& objs,int max_depth)
    {
        Query* q = _makeQuery(max_depth);
        int res = q->_getObj(objs,max_depth);
        delete q;
        return res;
    }

    template <typename OWNER, typename RELATED>
    void M2MQuerySet<OWNER,RELATED>::debugPrint() const
    {
        std::string q_str ="SELECT ";
        ManyToMany<OWNER,RELATED>::_staticNameAttrs(q_str,ORM_DEFAULT_MAX_DEPTH,_db);

        q_str+="\nFROM ";
        ManyToMany<OWNER,RELATED>::_staticNameTables(q_str,ORM_DEFAULT_MAX_DEPTH,_db);

        const int filters_size = _filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";
            auto begin = _filters.begin();
            const auto& end = _filters.end();
            std::cout<<q_str;
            q_str.clear();

            begin->debugPrint(ManyToMany<OWNER,RELATED>::staticGetDefaultDataBase());

            while(++begin != end)
            {
                std::cout<<" AND ";
                begin->debugPrint(ManyToMany<OWNER,RELATED>::staticGetDefaultDataBase());
            }
            std::cout<<") ";
        }

        int _size = _orderBy.size();
        if(_size >0)
        {
            std::cout<<" ORDER BY ";
            auto begin = _orderBy.begin();
            const auto& end = _orderBy.end();
            std::cout<<*begin;

            while(++begin != end)
            {
                std::cout<<" ,"<<*begin;
            }
        }

        if(_limitCount > 0)
        {
            std::cout<<_db._limit(_limitSkip,_limitCount);
        }
    };

    template <typename OWNER, typename RELATED>
    Query* M2MQuerySet<OWNER,RELATED>::_makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        ManyToMany<OWNER,RELATED>::_nameAttrs(q_str,max_depth,_db);

        q_str+="\nFROM ";
        ManyToMany<OWNER,RELATED>::_nameTables(q_str,max_depth,_db);

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

        Query* q = _db.prepareQuery(q_str);

        if(filters_size > 0)
        {
            auto begin = _filters.begin();
            const auto& end = _filters.end();
            unsigned int index = _db._getInitialSetcolumnNumber();
            while(begin != end)
            {

                begin->_set(q,index);
                ++begin;
                ++index;
            }
        }

        return q;
    }
}
