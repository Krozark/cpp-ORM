#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>::M2MQuerySet(const ManyToMany<OWNER,RELATED>& m2m): limit_skip(0), limit_count(-1)
    {
        filters.emplace_back(new Filter<int>(makecolumname(m2m.table,m2m._owner),"exact",m2m.owner.pk));
    }

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>::~M2MQuerySet()
    {
        for(auto* it : filters)
            delete it;
        for(auto* it: excludes)
            delete it;
    }


    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>::M2MQuerySet(M2MQuerySet&& tmp)
    {
        std::swap(filters,tmp.filters);
        std::swap(excludes,tmp.excludes);
        std::swap(order_by,tmp.order_by);
        limit_skip = tmp.limit_skip;
        limit_count = tmp.limit_count;
    }

    template <typename M2M,typename OWNER, typename RELATED>
    template<typename U,typename ... Args>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::filter(const U& value,const std::string& operande,const std::string& column,const Args& ... args)
    {
        filters.emplace_back(new Filter<U>(makecolumname(M2M::_related,column,args ...),operande,value));
        return *this;
    };

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::orderBy(const std::string& column,const char order)
    {
        if( order == '-')
            order_by.push_back(makecolumname(M2M::_related,column)+" DESC");
        else
            order_by.push_back(makecolumname(M2M::_related,column)+" ASC");
        return *this;
    }

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::orderBy(std::string&& column,const char order)
    {
        if( order == '-')
            order_by.push_back(makecolumname(M2M::table,column)+" DESC");
        else
            order_by.push_back(makecolumname(M2M::table,column)+" ASC");
        return *this;
    }

    template <typename M2M,typename OWNER, typename RELATED>
    template<typename U,typename ... Args>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::exclude(const U& value,const std::string& operande,const std::string& column,const Args& ... args)
    {
        excludes.emplace_back(new Filter<U>(makecolumname(M2M::_related,column,args ...),operande,value));
        return *this;
    };

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::limit(const unsigned int& count)
    {
        limit_count = static_cast<int>(count);
    };

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::limit(const unsigned int& skip,const unsigned int& count)
    {
        limit_skip = static_cast<int>(skip);
        limit_count = static_cast<int>(count);
    }


    template <typename M2M,typename OWNER, typename RELATED>
    int M2MQuerySet<M2M,OWNER,RELATED>::get(typename std::list<std::shared_ptr<RELATED>>& objs,int max_depth)
    {
        Query* q = makeQuery(max_depth);
        int res = q->getObj(objs,max_depth);
        delete q;
        return res;
    }

    template <typename M2M,typename OWNER, typename RELATED>
    void M2MQuerySet<M2M,OWNER,RELATED>::__print__() const
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

    template <typename M2M,typename OWNER, typename RELATED>
    template<typename ... Args>
    std::string M2MQuerySet<M2M,OWNER,RELATED>::makecolumname(const std::string& prefix,const std::string& column,Args&& ...args)
    {
        return makecolumname(JOIN_ALIAS(prefix,column),args...);
    }

    template <typename M2M,typename OWNER, typename RELATED>
    std::string M2MQuerySet<M2M,OWNER,RELATED>::makecolumname(const std::string& prefix,const std::string& column)
    {
        return M2M::bdd_used->escapecolumn(prefix)
            +"."+M2M::bdd_used->escapecolumn(column);
    }

    template <typename M2M,typename OWNER, typename RELATED>
    Query* M2MQuerySet<M2M,OWNER,RELATED>::makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        M2M::nameAttrs(q_str,max_depth);

        q_str+="\nFROM ";
        M2M::nameTables(q_str,max_depth);

        const int filters_size = filters.size();
        const int excludes_size = excludes.size();

        {//filters and excludes
            if(filters_size > 0 or excludes_size >0)
                q_str+=" \nWHERE (";
            if(filters_size > 0)
            {
                auto begin = filters.begin();
                const auto& end = filters.end();

                q_str+= (*begin)->column
                    +RELATED::bdd_used->formatPreparedValue((*begin)->ope);

                while(++begin != end)
                {
                    q_str+=" AND "
                        +(*begin)->column
                        +RELATED::bdd_used->formatPreparedValue((*begin)->ope);
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
                    +RELATED::bdd_used->formatPreparedValue((*begin)->ope);

                while(++begin != end)
                {
                    q_str+=" AND "
                        +(*begin)->column
                        +RELATED::bdd_used->formatPreparedValue((*begin)->ope);
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
            q_str+= M2M::bdd_used->limit(limit_skip,limit_count);

        Query* q = M2M::bdd_used->prepareQuery(q_str);

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
                }
            }
        }
        
        return q;
    }
}
