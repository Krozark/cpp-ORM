#ifndef ORM_CACHE_HPP
#define ORM_CACHE_HPP

#include <unordored_map>
#include <string>
#include <shared_ptr>

#include <ORM/models/SQLObjectBase>

namespace orm
{
    template<typename T>
    class Cache
    {
        public:
            std::shared_ptr<T>& getOrCreate(const int& pk);

        private:
            std::unordored_map<int,std::shared_ptr<SQLObjectBase> > map;
    }
}
#include <ORM/core/Cache.tpl>
#endif
