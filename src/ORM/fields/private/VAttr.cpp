#include <ORM/fields/private/VAttr.hpp>
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/backends/DB.hpp>

namespace orm
{
    VAttr::VAttr(const std::string& col) : _modified(false), _column(col)
    {
    };

    VAttr::~VAttr()
    {
    }

    std::ostream& operator<<(std::ostream& output,const VAttr& self)
    {
        return self.printValue(output);
    };
    const std::string& VAttr::getColumn() const
    {
        return _column;
    }

    void VAttr::registerAttr(SqlObjectBase& object)
    {
        object.attrs.emplace_back(this);
    }

    void VAttr::_beforeSave(){}

    void VAttr::_afterSave(){}

    void VAttr::_beforeUpdate(){}

    void VAttr::_afterUpdate(){}

    std::string VAttr::_makeName(DB& db, const std::string& prefix,int max_depth) const
    {
        return ", "+db._escapeColumn(prefix)+"."+db._escapeColumn(_column)+" AS "+JOIN_ALIAS(prefix,_column);
    }

};
