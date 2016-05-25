#include <ORM/fields/private/VFK.hpp>
#include <ORM/models/SqlObjectBase.hpp>

namespace orm
{
    VFK::VFK(const std::string& column,bool nullable) : VAttr(column) , fk(-1), nullable(nullable)
    {
    }

    int VFK::getFk()const
    { 
        return fk;
    }

    void VFK::registerAttr(SqlObjectBase& object)
    {
        object.attrs.emplace_back(this);
        object.fks.emplace_back(this);
    }

    bool VFK::save(bool recursive)
    {
        return this->save(recursive, getDefaultDataBase());
    }

    bool VFK::del(bool recursive)
    {
        return this->del(recursive, getDefaultDataBase());
    }

    bool VFK::set(const std::string&)
    {
        return false;
    }

    std::string VFK::asString()const
    {
        return std::to_string(fk);
    }

};
