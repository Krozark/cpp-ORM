#ifndef ORM_QUERYSET_HPP
#define ORM_QUERYSET_HPP

#include <ORM/backends/Filter.hpp>
#include <ORM/core/Cache.hpp>

namespace orm
{
    template <typename T>
    class QuerySet
    {
        public:
            template<typename U>
            QuerySet& filter(const std::string& colum,const std::string operande, const U& value);
            template<typename U,typename ... Args>
            QuerySet& filter(Filter<U>&& filter,Args&& ... args);

            QuerySet& orderBy(const std::string& colum);

            QuerySet& exclude();

            QuerySet& agregate();

            QuerySet& limite(int max);
            QuerySet& limite(int min,int max);

            T get();
            bool get(T& obj);
            bool get(typename std::list<Cache<T>::type_ptr>& obj);


        private:
            QuerySet();
            QuerySet(const QuerySet&) = delete;
            QuerySet& operator=(const QuerySet&) = delete;

            std::vector<Filter> filters;
            std::vector<std::string> order_by;
                        
    };
}
#include <ORM/backends/QuerySet.tpl>
#endif
