#ifndef ORM_DATABASEMIXIN_HPP
#define ORM_DATABASEMIXIN_HPP

namespace orm
{
    class DB;
    
    template<typename T>
    class DataBaseMixin
    {
        public:
            static DB& staticGetDefaultDataBase();

            static std::shared_ptr<orm::DB> defaultDBConnection; ///< db use to stor the object

    };
}
#include <ORM/core/DataBaseMixin.tpl>
#endif
