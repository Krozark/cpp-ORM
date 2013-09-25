#include <ORM/fields/private/VAttr.hpp>
#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/backends/Bdd.hpp>

namespace orm 
{
    VAttr::VAttr(const std::string& col) : colum(col), modify(false)
    {
    };

    std::ostream& operator<<(std::ostream& output,const VAttr& self)
    {
        self.print(output);
        return output;
    };
    const std::string& VAttr::getColum() const
    {
        return colum;
    }
    
    void VAttr::registerAttr(SQLObjectBase& object)
    {
        object.attrs.emplace_back(this);
    }

    std::string VAttr::makeName(const Bdd* bdd, const std::string& prefix,int max_depth) const
    {
        return ", "+bdd->escapeColum(prefix)+"."+bdd->escapeColum(colum)+" AS "+JOIN_ALIAS(prefix,colum);
    }
};
