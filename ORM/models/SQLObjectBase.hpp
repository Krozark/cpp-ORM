#ifndef ORM_SQLOBJECTBASE_HPP
#define ORM_SQLOBJECTBASE_HPP

#include <vector>
#include <ostream>

#include <ORM/externals.hpp>

namespace orm
{
    class Query;
    class VAttr;
    class Bdd;
    class VFK;
    template<typename T> class Register;
    template<typename T> class FKBase;
    template<typename T> class SQLObject;


    class SQLObjectBase
    {
        public:
            SQLObjectBase();

            SQLObjectBase(const SQLObjectBase&)=delete;
            SQLObjectBase& operator=(const SQLObjectBase&)=delete;

            bool loadFromBdd(const Query& query,int max_depth);
            virtual bool save(bool recursive=false) = 0;
            virtual bool del(bool recursive=false) = 0;

            /**
             * \brief Display the object in json
             **/
            friend std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self);


        protected:
            friend class Bdd;
            template<typename T> friend class FKBase;
            friend class VFK;
            friend class VAttr;
            template<typename T> friend class Register;
            template<typename T> friend class SQLObject;

            int pk;
            std::vector<VAttr*> attrs;
            std::vector<VFK*> fks;

            bool loadFromBdd(const Query& query,const std::string& prefix,int max_depth);

            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth)const =0;
            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth)const =0;
            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth)const =0;

            virtual const std::string& getTable() const = 0;
            virtual const Bdd* getBdd() const = 0;
    };
};


#endif
