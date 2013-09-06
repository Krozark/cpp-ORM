#include <ORM/fields/private/VFK.hpp>
#include <ORM/models/SQLObjectBase.hpp>

namespace orm
{
    VFK::VFK(const std::string& colum,bool nullable) : VAttr(colum) , fk(-1), loaded(false), nullable(nullable)
    {
    }

    void VFK::registerAttr(SQLObjectBase& object)
    {
        object.attrs.emplace_back(this);
        object.fks.emplace_back(this);
    }
};
