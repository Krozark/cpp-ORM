#include "SQLObjectBase.hpp"
#include "VAttr.hpp" 
#include "Query.hpp"

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
        if(res)
            query.get(pk,"id");
        return res;
    };

    void SQLObjectBase::registerAttr(VAttr& attr)
    {
        attrs.emplace_back(&attr);
    };

    std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self)
    {
        output<<"[id/pk]:"<<self.pk<<" ";
        for(VAttr* attr: self.attrs)
            output<<"["<<attr->getColum()<<"]:"<<*attr<<" ";
        return output;
    };

};
