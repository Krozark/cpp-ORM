#ifndef ORM_VFK_HPP
#define ORM_VFK_HPP

#include <ORM/fields/VAttr.hpp>

namespace orm
{
    class SQLObjectBase;

    class VFK : public VAttr
    {
        public:
            VFK(const std::string& colum);
            virtual const SQLObjectBase& getObject()const = 0;
            virtual void registerAttr(SQLObjectBase&);

        protected:
            int fk;
    };
}
#endif
