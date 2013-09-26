#ifndef ORM_FK_HPP
#define ORM_FK_HPP

#include <ORM/fields/private/FKBase.hpp>

namespace orm
{
    template<typename T,bool NULLABLE>
    class FK : public FKBase<T>
    {
        public:
            /**
             * \brief Construct a FK
             *
             * \param column colum where the fk is stored
             **/
            FK(const std::string& column);

            FK(const FK&) = delete;
    };
}

#include <ORM/fields/FK.tpl>

#endif
