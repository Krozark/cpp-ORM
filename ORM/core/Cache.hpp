#ifndef ORM_CACHE_HPP
#define ORM_CACHE_HPP

#include <ORM/backends/Query.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace orm
{
    template<typename T> class SQLObject;

    template<typename T>
    class Cache
    {
        public:
            //make query to get object if not in cache
            std::shared_ptr<T>& getOrCreate(const unsigned int& pk);
            //construct object from query if not in cache
            std::shared_ptr<T>& getOrCreate(const unsigned int& pk,const Query& query);
            //if tmp->pk if cache, reture cache[pk] and delete tmp, else make tmp as shared_ptr
            std::shared_ptr<T>& getOrCreate(T* tmp);

            void __print__();


        private:
            friend class SQLObject<T>;
            std::unordered_map<int,std::shared_ptr<T> > map;
    };
}
#include <ORM/core/Cache.tpl>
#endif
