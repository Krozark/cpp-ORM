#include <ORM/fields/VFK.hpp>
#include <ORM/models/SQLObjectBase.hpp>

namespace orm
{
    VFK::VFK(const std::string& colum) : VAttr(colum) , fk(-1), loaded(false)
    {
    }

    void VFK::registerAttr(SQLObjectBase& object)
    {
        object.attrs.emplace_back(this);
        object.fks.emplace_back(this);
    }
};
