#ifndef ORM_VFK_HPP
#define ORM_VFK_HPP

#include <ORM/fields/private/VAttr.hpp>

namespace orm
{
    class SQLObjectBase;
    template<typename T> class SQLObject;

    class VFK : public VAttr
    {
        public:
            VFK(const std::string& column,const bool nullable=true);

            virtual const SQLObjectBase& getObject(int max_depth=ORM_DEFAULT_MAX_DEPTH)= 0;
            virtual void registerAttr(SQLObjectBase&);
            virtual bool save(bool recursive=false) = 0;            
            virtual bool del(bool recursive=false) = 0;

            virtual std::ostream& print_value(std::ostream& output)const;


        protected:
            template<typename T> friend class SQLObject;
            int fk;
            bool loaded;
            const bool nullable;

            virtual void incDepth(int& depth,int max_depth)const = 0;



    };
}
#endif
