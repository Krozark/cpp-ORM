#ifndef ORM_FK_HPP
#define ORM_FK_HPP

#include <ORM/fields/private/FKBase.hpp>

namespace orm
{
    template<typename T,bool NULLABLE>
    class FK : public FKBase<T>
    {
        public:
            //FK(const int& id,const std::string& colum);
            FK(const std::string& colum);

            FK(const FK&) = delete;
    };
}

#include <ORM/fields/FK.tpl>

#endif
