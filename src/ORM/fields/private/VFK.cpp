#include <ORM/fields/private/VFK.hpp>
#include <ORM/models/SQLObjectBase.hpp>

namespace orm
{
    VFK::VFK(const std::string& column,bool nullable) : VAttr(column) , fk(-1), loaded(false), nullable(nullable)
    {
    }

    void VFK::registerAttr(SQLObjectBase& object)
    {
        object.attrs.emplace_back(this);
        object.fks.emplace_back(this);
    }

    std::ostream& VFK::print_value(std::ostream& output)const
    {
        return (output<<fk);
    }

};
