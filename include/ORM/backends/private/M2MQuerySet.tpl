#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>::M2MQuerySet(const ManyToMany<OWNER,RELATED>& m2m,DB& db): limit_skip(0), limit_count(-1), db(db)
    {
        filters.emplace_back(new Filter<M2M,int>(DB::makecolumname(*M2M::default_connection,m2m.table,m2m._owner),"exact",m2m.owner.pk));
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
    template<typename U,typename ... Args>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::filter(const U& value,const std::string& operande,const std::string& column,const Args& ... args)
    {
        filters.emplace_back(new Filter<M2M,U>(DB::makecolumname(*M2M::default_connection,M2M::_related,column,args ...),operande,value));
        return *this;
    };

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::orderBy(const std::string& column,const char order)
    {
        if( order == '-')
            order_by.push_back(DB::makecolumname(*M2M::default_connection,M2M::_related,column)+" DESC");
        else
            order_by.push_back(DB::makecolumname(*M2M::default_connection,M2M::_related,column)+" ASC");
        return *this;
    }

    template <typename M2M,typename OWNER, typename RELATED>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::orderBy(std::string&& column,const char order)
    {
        if( order == '-')
            order_by.push_back(DB::makecolumname(*M2M::default_connection,M2M::table,column)+" DESC");
        else
            order_by.push_back(DB::makecolumname(*M2M::default_connection,M2M::table,column)+" ASC");
        return *this;
    }

    template <typename M2M,typename OWNER, typename RELATED>
    template<typename U,typename ... Args>
    M2MQuerySet<M2M,OWNER,RELATED>& M2MQuerySet<M2M,OWNER,RELATED>::exclude(const U& value,const std::string& operande,const std::string& column,const Args& ... args)
    {
        excludes.emplace_back(new Filter<M2M,U>(DB::makecolumname(*M2M::default_connection,M2M::_related,column,args ...),operande,value));
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
            u->__print__(*OWNER::default_connection);
        std::cout<<"exclude: ";
        for (auto* u :  excludes)
            u->__print__(*OWNER::default_connection);
        std::cout<<"order_by: ";
        for (auto& u :  order_by)
            std::cout<<u<<" ";
        std::cout<<std::endl<<"limit:<"<<limit_skip<<","<<limit_count<<">"<<std::endl;
    };

    template <typename M2M,typename OWNER, typename RELATED>
    Query* M2MQuerySet<M2M,OWNER,RELATED>::makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        M2M::nameAttrs(q_str,max_depth,db);

        q_str+="\nFROM ";
        M2M::nameTables(q_str,max_depth,db);

        const int filters_size = filters.size();
        const int excludes_size = excludes.size();

        {//filters and excludes
            if(filters_size > 0 or excludes_size >0)
                q_str+=" \nWHERE (";
            if(filters_size > 0)
            {
                auto begin = filters.begin();
                const auto& end = filters.end();

                (*begin)->toQuery(q_str,db);

                while(++begin != end)
                {
                    q_str+=" AND ";
                    (*begin)->toQuery(q_str,db);
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

                (*begin)->toQuery(q_str,db);

                while(++begin != end)
                {
                    q_str+=" AND ";
                    (*begin)->toQuery(q_str,db);
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
            q_str+= db.limit(limit_skip,limit_count);

        Query* q = db.prepareQuery(q_str);

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
