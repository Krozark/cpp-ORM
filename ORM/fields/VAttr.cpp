#include <ORM/fields/VAttr.hpp>
#include <ORM/models/SQLObjectBase.hpp>

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
};
