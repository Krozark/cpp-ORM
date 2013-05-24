#include "VAttr.hpp" 

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

};
