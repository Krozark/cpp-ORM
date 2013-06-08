#ifndef ORM_VATTR_HPP
#define ORM_VATTR_HPP

#include <string>
#include <ORM/debug.hpp>

namespace orm
{
    class Query;
    class Bdd;
    class SQLObjectBase;
    template<typename T> class Register;

    class VAttr
    {
        public:
            VAttr(const std::string& colum);

            VAttr(const VAttr&) = delete;
            VAttr& operator=(const VAttr&) = delete;

            friend std::ostream& operator<<(std::ostream& output,const VAttr& self);

            const std::string& getColum() const;

            virtual void registerAttr(SQLObjectBase&);

        protected:
            friend class Bdd;
            friend class SQLObjectBase;
            template<typename T> friend class Register;

            bool modify;
            const std::string& colum;
            virtual void print(std::ostream& output) const =0;
            virtual bool set(Query& query,const unsigned int& colum) const = 0;
            virtual bool get(const Query& query) = 0;
    };
};

#endif
