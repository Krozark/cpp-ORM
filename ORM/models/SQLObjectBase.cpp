#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/VAttr.hpp>
#include <ORM/fields/VFK.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{
    SQLObjectBase::SQLObjectBase() : pk(-1)
    {
    }; 

    bool SQLObjectBase::loadFromBdd(const Query& query,int max_depth)
    {
        return loadFromBdd(query,"",max_depth);
    };

    bool SQLObjectBase::loadFromBdd(const Query& query,const std::string& prefix,int max_depth)
    {
        bool res = true;
        const std::string& table_alias(JOIN_ALIAS(prefix,getTable()));
        for(VAttr* attr: attrs)
        {
            res = res && attr->get(query,table_alias,max_depth);
        }
        if(res)
        {
            query.get(pk,JOIN_ALIAS(table_alias,"id"));
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
