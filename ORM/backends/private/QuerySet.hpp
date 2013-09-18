#ifndef ORM_QUERYSET_HPP
#define ORM_QUERYSET_HPP

#include <ORM/backends/Filter.hpp>
#include <ORM/core/Cache.hpp>

namespace orm
{
    template<typename T> class SQLObject;

    template <typename T>
    class QuerySet
    {
        public:
            QuerySet(QuerySet<T>&& tmp);

            template<typename U,typename ... Args>
            QuerySet<T>& filter(const U& value,const std::string& operande,const std::string& colum,const Args& ... args);
            QuerySet<T>& filter(const std::list<Filter>& filter_list);
            QuerySet<T>& filter(std::list<Filter>&& filter_list);

            QuerySet<T>& orderBy(const std::string& colum);
            QuerySet<T>& orderBy(std::string&& colum);
            //QuerySet& orderBy(int,const std::string& colum);

            template<typename U,typename ... Args>
            QuerySet<T>& exclude(const U& value,const std::string& operande,const std::string& colum,const Args& ... args);
            QuerySet<T>& exclude(const std::list<Filter>& exclude_list);
            QuerySet<T>& exclude(std::list<Filter>&& exclude_list);

            QuerySet<T>& limit(const unsigned int& max);
            QuerySet<T>& limit(const unsigned int& min,const unsigned int& max);

            //QuerySet& agregate();

            bool get(T& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);
            //bool get(typename std::list<Cache<T>::type_ptr>& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            void __print__() const;


        private:
            friend class SQLObject<T>;

            explicit QuerySet();

            template<typename ... Args>
            static std::string makeColumName(const std::string& prefix,const std::string& colum,Args&& ... args);
            template<typename ... Args>
            static std::string makeColumName(std::string&& prefix,std::string&& colum,Args&& ... args);
            static std::string makeColumName(std::string colum);

            Query* makeQuery(int max_depth);


            QuerySet(const QuerySet&) = delete;
            QuerySet& operator=(const QuerySet&) = delete;

            std::list<Filter> filters;
            std::list<Filter> excludes;
            std::vector<std::string> order_by;
            int limit_min,limit_max;
                        
    };
}
#include <ORM/backends/private/QuerySet.tpl>
#endif
