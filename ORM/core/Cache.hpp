#ifndef ORM_CACHE_HPP
#define ORM_CACHE_HPP

#include <unordered_map>
#include <string>
#include <memory>

namespace orm
{
    template<typename T>
    class Cache
    {
        public:
            std::shared_ptr<T>& getOrCreate(const unsigned int& pk);

        private:
            std::unordered_map<int,std::shared_ptr<T> > map;
    };
}
#include <ORM/core/Cache.tpl>
#endif
