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

    void SQLObjectBase::nameAttrs(std::string& q_str)const
    {
        const Bdd* bdd = getBdd();
        const std::string& table = getTable();

        q_str+= bdd->escape_colum(table)+"."+bdd->escape_colum("id")+" AS "+bdd->escape_value(table+".id");
        
        {
            const int size = attrs.size();
            for(int i=0;i<size;++i)
            {
                const std::string& col = attrs[i]->getColum();
                q_str+= ", "+col+" AS "+bdd->escape_value(col);
            }
        }
        {
            const int size = fks.size();
            for(int i=0;i<size;++i)
            {
                q_str+="\n";
                const SQLObjectBase& object = fks[i]->getObject();
                q_str+=",";
                object.nameAttrs(q_str);
            }
        }
    }

    void SQLObjectBase::nameTables(std::string& q_str)const
    {
        q_str+= getTable();

        const int size = fks.size();
        for(int i=0;i<size;++i)
        {
            q_str+=",";
            fks[i]->getObject().nameTables(q_str);
        }
    }

    void SQLObjectBase::nameFks(std::string& q_str)const
    {
        const int size = fks.size();
        const Bdd* bdd = getBdd();
        const std::string& table = getTable();

        for(int i=0;i<size;++i)
        {
            const SQLObjectBase& object = fks[i]->getObject();
            q_str+= " AND "+fks[i]->getColum()
                +" "+bdd->operators.at("exact")
                +bdd->escape_colum(object.getTable())+"."+bdd->escape_colum("id");
            object.nameFks(q_str);
        }
    }

};
