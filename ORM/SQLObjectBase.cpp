#include "SQLObjectBase.hpp"
#include "VAttr.hpp" 
#include "Query.hpp"
#include "VFK.hpp"

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

    void SQLObjectBase::nameAttrs(std::string& q_str)const
    {
        const Bdd* bdd = getBdd();
        const std::string& table = getTable();

        q_str+= bdd->escape_colum(table)+"."+("id");
        
        {
            const int size = attrs.size();
            for(int i=0;i<size;++i)
            {
                q_str+= ","+bdd->escape_colum(table)+"."+bdd->escape_colum(attrs[i]->getColum());
            }
        }
        {
            const int size = fks.size();
            for(int i=0;i<size;++i)
            {
                const SQLObjectBase& object = fks[i]->getObject();
                q_str+=",";
                object. nameAttrs(q_str);
            }
        }
        q_str+="\n";
    }

};
