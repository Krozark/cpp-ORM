#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>
#include <ORM/fields/private/VFK.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{
    SQLObjectBase::SQLObjectBase() : pk(-1)
    {
    }; 

    int SQLObjectBase::getPk()const
    {
        return pk;
    }

    bool SQLObjectBase::loadFromBdd(const Query& query,int max_depth)
    {
        int prefix=getBdd()->getInitialGetcolumnNumber() -1;
        return loadFromBdd(query,prefix,max_depth);
    };

    bool SQLObjectBase::loadFromBdd(const Query& query,int& prefix,int max_depth)
    {
        ++prefix;

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr("<<prefix<<") : id"<<BLANC<<std::endl;
        #endif

        bool res = query.get(pk,prefix); //id

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        if(not res)
            std::cerr<<ROUGE<<"[ATTR] get attr("<<prefix<<") : id"<<" fail"<<BLANC<<std::endl;
        #endif
        for(VAttr* attr: attrs)
        {
            ++prefix;
            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            std::cerr<<MAGENTA<<"[ATTR] get attr("<<prefix<<") : "<<attr->getcolumn()<<BLANC<<std::endl;
            #endif

            bool tmp = attr->get(query,prefix,max_depth); //incrementation of column number for the next

            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            if(not tmp)
                std::cerr<<ROUGE<<"[ATTR] get attr("<<prefix<<") : "<<attr->getcolumn()<<" fail"<<BLANC<<std::endl;
            #endif
            res = (res and  tmp);
        }

        #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
        if(not res)
        {
            std::cerr<<ROUGE<<"[GET OBJ] SQLObjectBase::loadFromBdd(const Query& query,int & prefix,int max_depth) failed : One or more attr not get"<<BLANC<<std::endl;
        }
        #endif
        return res;
    };


    std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self)
    {
        output<<"{ \"pk\":"<<self.pk;
        for(VAttr* attr: self.attrs)
            output<<", \""<<attr->getcolumn()<<"\":"<<*attr;
        output<<"}";
        return output;
    };
};
