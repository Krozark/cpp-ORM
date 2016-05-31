#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>
#include <ORM/fields/private/VFK.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{

    const std::string SqlObjectBase::ORM_MAKE_NAME(pk) = ORM_MAKE_NAME_VALUE(SqlObjectBase, "pk");

    SqlObjectBase::SqlObjectBase() : pk(-1)
    {
    }

    SqlObjectBase::~SqlObjectBase()
    {
    }

    int SqlObjectBase::getPk()const
    {
        return pk;
    }

    bool SqlObjectBase::save(bool recursive)
    {
        return this->save(recursive, getDefaultDataBase());
    }

    bool SqlObjectBase::del(bool recursive)
    {
        return this->del(recursive, getDefaultDataBase());
    }

    std::vector<VAttr*>& SqlObjectBase::getAttributes()
    {
        return attrs;
    }

    VAttr* SqlObjectBase::getAttribute(const std::string& name)
    {
        VAttr* res = nullptr;
        const unsigned int size = attrs.size();
        for (unsigned int i = 0; i < size; ++i)
        {
            if (attrs[i]->getcolumn() == name)
            {
                res = attrs[i];
                break;
            }
        }
        return res;
    }

    std::ostream& operator<<(std::ostream& output, const SqlObjectBase& self)
    {
        output << "{ \"" << SqlObjectBase::ORM_MAKE_NAME(pk) << "\":" << self.pk;
        for (VAttr* attr : self.attrs)
            output << ", \"" << attr->getcolumn() << "\":" << *attr;
        output << "}";
        return output;
    };


    ////////////////////////////// Private / protected /////////////////////


    void SqlObjectBase::before_save(){}

    void SqlObjectBase::after_save(){}

    void SqlObjectBase::before_update(){}

    void SqlObjectBase::after_update(){}

    void SqlObjectBase::before_load(){};

    void SqlObjectBase::after_load(){};


    bool SqlObjectBase::loadFromDB(const Query& query,int max_depth)
    {
        int prefix=query._db._getInitialGetcolumnNumber() -1;
        return loadFromDB(query,prefix,max_depth);
    };


    bool SqlObjectBase::loadFromDB(const Query& query,int& prefix,int max_depth)
    {
        ++prefix;

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<ORM_COLOUR_REDMAGENTA<<"[ATTR] get attr("<<prefix<<") : id"<<ORM_COLOUR_REDNONE<<std::endl;
        #endif

        bool res = query._get(pk,prefix); //id


        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        if(not res)
            std::cerr<<ORM_COLOUR_REDRED<<"[ATTR] get attr("<<prefix<<") : id"<<" fail"<<ORM_COLOUR_REDNONE<<std::endl;
        #endif
        before_load();
        for(VAttr* attr: attrs)
        {
            ++prefix;
            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            std::cerr<<ORM_COLOUR_REDMAGENTA<<"[ATTR] get attr("<<prefix<<") : "<<attr->getcolumn()<<ORM_COLOUR_REDNONE<<std::endl;
            #endif

            bool tmp = attr->get(query,prefix,max_depth); //incrementation of column number for the next

            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            if(not tmp)
                std::cerr<<ORM_COLOUR_REDRED<<"[ATTR] get attr("<<prefix<<") : "<<attr->getcolumn()<<" fail"<<ORM_COLOUR_REDNONE<<std::endl;
            #endif
            res = (res and  tmp);
        }
        after_load();

        #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
        if(not res)
        {
            std::cerr<<ORM_COLOUR_REDRED<<"[GET OBJ] SqlObjectBase::loadFromDB(const Query& query,int & prefix,int max_depth) failed : One or more attr not get"<<ORM_COLOUR_REDNONE<<std::endl;
        }
        #endif
        return res;
    };

};
