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
            Cache();

            ~Cache();
            //Cache(const Cache<T>&)=delete;
            //Cache<T>& operator=(const Cache<T>&)=delete;
            
            typedef std::shared_ptr<T> type_ptr;
            
            //make query to get object if not in cache
            type_ptr& getOrCreate(const unsigned int& pk,int max_depth);

            //construct object from query if not in cache
            type_ptr& getOrCreate(const unsigned int& pk,const Query& query,const std::string& prefix,int max_depth);

            //if tmp->pk if cache, reture cache[pk] and delete tmp, else make tmp as type_ptr
            type_ptr& getOrCreate(T* tmp);

            //delete object of specified pk
            void del(const unsigned int& pk);

            void __print__();



        private:
            friend class SQLObject<T>;
            bool add(T& obj);
            std::unordered_map<int,type_ptr> map;
    };
}
#include <ORM/core/Cache.tpl>
#endif
