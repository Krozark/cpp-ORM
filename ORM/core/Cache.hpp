#ifndef ORM_CACHE_HPP
#define ORM_CACHE_HPP

#include <unordored_map>
#include <string>
#include <shared_ptr>

#include <ORM/models/SQLObjectBase>

namespace orm
{
    class Cache
    {
        public:
            template<typename T>
            std::shared_ptr<SQLObjectBase>& getOrCreate(const int& pk);

        private:
            std::unordored_map<std::string,std::shared_ptr<SQLObjectBase> > map;
    }
}
#include <ORM/core/Cache.tpl>
#endif
