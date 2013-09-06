#ifndef ORM_VFK_HPP
#define ORM_VFK_HPP

#include <ORM/fields/VAttr.hpp>

namespace orm
{
    class SQLObjectBase;
    template<typename T> class SQLObject;

    class VFK : public VAttr
    {
        public:
            VFK(const std::string& colum);
            virtual const SQLObjectBase& getObject(int max_depth=ORM_DEFAULT_MAX_DEPTH)= 0;
            virtual void registerAttr(SQLObjectBase&);
            virtual bool save(bool recursive=false,bool force=false) = 0;            

        protected:
            template<typename T> friend class SQLObject;
            int fk;
            bool loaded;
    };
}
#endif
