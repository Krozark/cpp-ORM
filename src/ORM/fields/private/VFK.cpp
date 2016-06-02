#include <ORM/fields/private/VFK.hpp>
#include <ORM/models/SqlObjectBase.hpp>

namespace orm
{
    VFK::VFK(const std::string& column,bool nullable) : VAttr(column) , _fk(-1), _nullable(nullable)
    {
    }

    int VFK::getFk()const
    {
        return _fk;
    }

    void VFK::registerAttr(SqlObjectBase& object)
    {
        object._attributsVector.emplace_back(this);
        object._fkAttributsVector.emplace_back(this);
    }

    bool VFK::save(bool recursive)
    {
        return this->save(recursive, getDefaultDataBase());
    }

    bool VFK::del(bool recursive)
    {
        return this->del(recursive, getDefaultDataBase());
    }

    bool VFK::setValue(const std::string&)
    {
        return false;
    }

    std::string VFK::asString()const
    {
        return std::to_string(_fk);
    }

};
