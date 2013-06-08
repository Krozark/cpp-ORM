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

    template<typename T> class FK;


    class SQLObjectBase
    {
        public:
            SQLObjectBase();

            SQLObjectBase(const SQLObjectBase&)=delete;
            SQLObjectBase& operator=(const SQLObjectBase&)=delete;

            bool loadFromBdd(const Query& query);
            virtual bool save(bool force=false) = 0;
            virtual bool del() = 0;

            friend std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self);

        protected:
            friend class Bdd;
            template<typename T> friend class FK;
            friend class VFK;
            friend class VAttr;

            int pk;
            std::vector<VAttr*> attrs;
            std::vector<VFK*> fks;

            void nameAttrs(std::string& q_str)const;
            void nameTables(std::string& q_str)const;
            void nameFks(std::string& q_str)const;

            virtual const std::string& getTable() const = 0;
            virtual const Bdd* getBdd() const = 0;
    };
};


#endif
