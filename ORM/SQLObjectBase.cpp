#include "SQLObjectBase.hpp"
#include "VAttr.hpp" 

namespace orm
{
    SQLObjectBase::SQLObjectBase() : pk(-1)
    {
    }; 

    bool SQLObjectBase::loadFromBdd(const Query& query)
    {
        bool res = true;
        for(VAttr* attr: attrs)
        {
            res = res && attr->get(query);
        }
        return res;
    };

    void SQLObjectBase::registerAttr(VAttr& attr)
    {
        attrs.emplace_back(&attr);
    };

    std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self)
    {
        for(VAttr* attr: self.attrs)
            output<<*attr<<" ";
        return output;
    };

};
