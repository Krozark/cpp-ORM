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
        return _attributsVector;
    }

    VAttr* SqlObjectBase::getAttribute(const std::string& name)
    {
        VAttr* res = nullptr;
        const unsigned int size = _attributsVector.size();
        for (unsigned int i = 0; i < size; ++i)
        {
            if (_attributsVector[i]->getColumn() == name)
            {
                res = _attributsVector[i];
                break;
            }
        }
        return res;
    }

    std::ostream& operator<<(std::ostream& output, const SqlObjectBase& self)
    {
        output << "{ \"" << SqlObjectBase::ORM_MAKE_NAME(pk) << "\":" << self.pk;
        for (VAttr* attr : self._attributsVector)
            output << ", \"" << attr->getColumn() << "\":" << *attr;
        output << "}";
        return output;
    };


    ////////////////////////////// Private / protected /////////////////////


    void SqlObjectBase::_beforeSave(){}

    void SqlObjectBase::_afterSave(){}

    void SqlObjectBase::_beforeUpdate(){}

    void SqlObjectBase::_afterUpdate(){}

    void SqlObjectBase::_beforeLoad(){};

    void SqlObjectBase::_afterLoad(){};


    bool SqlObjectBase::_loadFromDB(const Query& query,int max_depth)
    {
        int prefix=query._db._getInitialGetcolumnNumber() -1;
        return _loadFromDB(query,prefix,max_depth);
    };


    bool SqlObjectBase::_loadFromDB(const Query& query,int& prefix,int max_depth)
    {
        ++prefix;

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<ORM_COLOUR_MAGENTA<<"[ATTR] get attr("<<prefix<<") : id"<<ORM_COLOUR_NONE<<std::endl;
        #endif

        bool res = query._get(pk,prefix); //id


        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        if(not res)
            std::cerr<<ORM_COLOUR_RED<<"[ATTR] get attr("<<prefix<<") : id"<<" fail"<<ORM_COLOUR_NONE<<std::endl;
        #endif
        _beforeLoad();
        for(VAttr* attr: _attributsVector)
        {
            ++prefix;
            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            std::cerr<<ORM_COLOUR_MAGENTA<<"[ATTR] get attr("<<prefix<<") : "<<attr->getColumn()<<ORM_COLOUR_NONE<<std::endl;
            #endif

            bool tmp = attr->_getFromQuery(query,prefix,max_depth); //incrementation of column number for the next

            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            if(not tmp)
                std::cerr<<ORM_COLOUR_RED<<"[ATTR] get attr("<<prefix<<") : "<<attr->getColumn()<<" fail"<<ORM_COLOUR_NONE<<std::endl;
            #endif
            res = (res and  tmp);
        }
        _afterLoad();

        #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
        if(not res)
        {
            std::cerr<<ORM_COLOUR_RED<<"[GET OBJ] SqlObjectBase::_loadFromDB(const Query& query,int & prefix,int max_depth) failed : One or more attr not get"<<ORM_COLOUR_NONE<<std::endl;
        }
        #endif
        return res;
    };

};
