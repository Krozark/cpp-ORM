#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/VAttr.hpp>
#include <ORM/fields/VFK.hpp>
#include <ORM/backends/Query.hpp>

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
        {
            query.get(pk,getTable()+".id");
        }
        return res;
    };


    std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self)
    {
        output<<"[id/pk]:"<<self.pk<<" ";
        for(VAttr* attr: self.attrs)
            output<<"["<<attr->getColum()<<"]:"<<*attr<<" ";
        return output;
    };
};
