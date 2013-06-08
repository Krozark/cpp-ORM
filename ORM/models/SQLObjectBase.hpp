#ifndef ORM_SQLOBJECTBASE_HPP
#define ORM_SQLOBJECTBASE_HPP

#include <vector>
#include <ostream>

#include <ORM/debug.hpp>

namespace orm
{
    class Query;
    class VAttr;
    class Bdd;
    class VFK;
    template<typename T> class Register;
    template<typename T> class FK;
    template<typename T> class SQLObject;


    class SQLObjectBase
    {
        public:
            SQLObjectBase();

            SQLObjectBase(const SQLObjectBase&)=delete;
            SQLObjectBase& operator=(const SQLObjectBase&)=delete;

            bool loadFromBdd(const Query& query);
            virtual bool save(bool recursive=false,bool force=false) = 0;
            virtual bool del() = 0;

            friend std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self);

        protected:
            friend class Bdd;
            template<typename T> friend class FK;
            friend class VFK;
            friend class VAttr;
            template<typename T> friend class Register;
            template<typename T> friend class SQLObject;

            int pk;
            std::vector<VAttr*> attrs;
            std::vector<VFK*> fks;

            virtual void _nameAttrs(std::string& q_str)const =0;
            virtual void _nameTables(std::string& q_str)const =0;
            virtual void _nameFks(std::string& q_str)const =0;

            virtual const std::string& getTable() const = 0;
            virtual const Bdd* getBdd() const = 0;
    };
};


#endif
