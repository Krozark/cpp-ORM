#include <ORM/fields/private/VAttr.hpp>
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/backends/DB.hpp>

namespace orm 
{
    VAttr::VAttr(const std::string& col) : modify(false), column(col)
    {
    };

    VAttr::~VAttr()
    {
    }

    std::ostream& operator<<(std::ostream& output,const VAttr& self)
    {
        self.print(output);
        return output;
    };
    const std::string& VAttr::getcolumn() const
    {
        return column;
    }
    
    void VAttr::registerAttr(SqlObjectBase& object)
    {
        object.attrs.emplace_back(this);
    }

    std::string VAttr::makeName(DB& db, const std::string& prefix,int max_depth) const
    {
        return ", "+db.escapeColumn(prefix)+"."+db.escapeColumn(column)+" AS "+JOIN_ALIAS(prefix,column);
    }

};
