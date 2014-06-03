#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>::M2MQuerySet(const ManyToMany<OWNER,RELATED>& m2m,DB& db): limit_skip(0), limit_count(-1), db(db)
    {
        filters.emplace_back(new Filter<ManyToMany<OWNER,RELATED>,int>(m2m.owner.pk,op::exact,m2m._owner));
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>::~M2MQuerySet()
    {
    }


    template <typename OWNER, typename RELATED>
    template<typename ... Args>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(Args&& ... args)
    {
        filters.emplace_back(Q<ManyToMany<OWNER,RELATED>>(std::forward<Args>(args)...));
        return *this;
    };

    template<typename OWNER,typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(const FilterSet<ManyToMany<OWNER,RELATED>>& f)
    {
        filters.emplace_back(f);
        return *this;
    }

    template<typename OWNER,typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(FilterSet<ManyToMany<OWNER,RELATED>>&& f)
    {
        filters.push_back(std::move(f));
        return *this;
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::orderBy(const std::string& column,const char order)
    {
        if( order == '-')
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" DESC");
        else
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" ASC");
        return *this;
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::orderBy(std::string&& column,const char order)
    {
        if( order == '-')
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" DESC");
        else
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" ASC");
        return *this;
    }


    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::limit(const unsigned int& count)
    {
        limit_count = static_cast<int>(count);
        return *this;
    };

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::limit(const unsigned int& skip,const unsigned int& count)
    {
        limit_skip = static_cast<int>(skip);
        limit_count = static_cast<int>(count);
        return *this;
    }   


    template <typename OWNER, typename RELATED>
    int M2MQuerySet<OWNER,RELATED>::get(typename std::list<std::shared_ptr<RELATED>>& objs,int max_depth)
    {
        Query* q = makeQuery(max_depth);
        int res = q->getObj(objs,max_depth);
        delete q;
        return res;
    }

    template <typename OWNER, typename RELATED>
    void M2MQuerySet<OWNER,RELATED>::__print__() const
    {
        std::cout<<"Filter: ";
        for (auto& u :  filters)
            u.__print__(*OWNER::default_connection);
        std::cout<<"order_by: ";
        for (auto& u :  order_by)
            std::cout<<u<<" ";
        std::cout<<std::endl<<"limit:<"<<limit_skip<<","<<limit_count<<">"<<std::endl;
    };

    template <typename OWNER, typename RELATED>
    Query* M2MQuerySet<OWNER,RELATED>::makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        ManyToMany<OWNER,RELATED>::nameAttrs(q_str,max_depth,db);

        q_str+="\nFROM ";
        ManyToMany<OWNER,RELATED>::nameTables(q_str,max_depth,db);

        const int filters_size = filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";
            auto begin = filters.begin();
            const auto& end = filters.end();

            (*begin)->toQuery(q_str,db);

            while(++begin != end)
            {
                q_str+=" AND ";
                (*begin)->toQuery(q_str,db);
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
            q_str+= db.limit(limit_skip,limit_count);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<BLEU<<"[Sql:makeQuery] "<<q_str<<"\nVALUES = (";
        #endif

        Query* q = db.prepareQuery(q_str);
        
        if(filters_size > 0)
        {
            auto begin = filters.begin();
            const auto& end = filters.end();
            unsigned int index = 1;
            while(begin != end)
            {

                begin->set(q,index);
                ++begin;
                ++index;
            }
        }

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<")"<<std::endl;
        #endif

        return q;
    }
}
