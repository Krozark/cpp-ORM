#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>
#include <ORM/fields/private/VFK.hpp>
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
        const std::string& table_alias = (prefix.size()>0)?prefix:getTable();
        for(VAttr* attr: attrs)
        {
            bool tmp = attr->get(query,table_alias,max_depth);
            res = res &&  tmp;
        }
        if(res)
        {
            query.get(pk,JOIN_ALIAS(table_alias,"id"));
        }
        #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
        else
        {
            std::cerr<<ROUGE<<"[GET OBJ] SQLObjectBase::loadFromBdd(const Query& query,const std::string& prefix,int max_depth) failed : One or more attr not get"<<BLANC<<std::endl;
        }
        #endif
        return res;
    };


    std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self)
    {
        output<<"{ \"pk\":"<<self.pk;
        for(VAttr* attr: self.attrs)
            output<<", \""<<attr->getColum()<<"\":"<<*attr;
        output<<"}";
        return output;
    };
};
