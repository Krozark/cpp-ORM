#ifndef ORM_VATTR_HPP
#define ORM_VATTR_HPP

#include <string>
#include <ORM/externals.hpp>

namespace orm
{
    class Query;
    class Bdd;
    class SQLObjectBase;
    template<typename T> class Register;

    class VAttr
    {
        public:
            VAttr(const std::string& column);

            VAttr(const VAttr&) = delete;
            VAttr& operator=(const VAttr&) = delete;

            friend std::ostream& operator<<(std::ostream& output,const VAttr& self);

            virtual std::ostream& print_value(std::ostream& output)const = 0;

            const std::string& getcolumn() const;

            virtual void registerAttr(SQLObjectBase&);

        protected:
            friend class Bdd;
            friend class SQLObjectBase;
            template<typename T> friend class Register;
            template<typename T> friend class SQLObject;

            bool modify;
            const std::string& column;
            virtual void print(std::ostream& output) const =0;
            virtual bool set(Query& query,const unsigned int& column) = 0;
            virtual bool get(const Query& query,int& prefix,int max_depth) = 0;

            virtual std::string makeName(const Bdd* bdd,const std::string& prefix,int max_depth) const;


    };
};

#endif
