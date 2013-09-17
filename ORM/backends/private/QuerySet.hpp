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
            QuerySet& filter(const U& value,const std::string& operande,const std::string& colum,const Args& ... args);

            /*template<typename ... Args>
            QuerySet& filter(Filter&& filter,Args&& ... args);*/

            /*QuerySet& orderBy(const std::string& colum);

            QuerySet& exclude();

            QuerySet& agregate();

            QuerySet& limite(int max);
            QuerySet& limite(int min,int max);

            T get();
            bool get(T& obj);
            bool get(typename std::list<Cache<T>::type_ptr>& obj);*/

            void __print__() const;


        private:
            friend class SQLObject<T>;

            template<typename ... Args>
            static std::string makeColumName(const std::string& prefix,const std::string& colum,Args&& ... args);
            template<typename ... Args>
            static std::string makeColumName(std::string&& prefix,std::string&& colum,Args&& ... args);
            static std::string makeColumName(std::string colum);

            explicit QuerySet();
            QuerySet(const QuerySet&) = delete;
            QuerySet& operator=(const QuerySet&) = delete;

            std::list<Filter> filters;
            //std::vector<std::string> order_by;
                        
    };
}
#include <ORM/backends/private/QuerySet.tpl>
#endif
