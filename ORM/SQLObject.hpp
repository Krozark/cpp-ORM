#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

//#include "Query.hpp"

#include <vector>

#include "VAttr.hpp" 


namespace orm
{
    class Bdd;
    class Query;
    //class VAttr;

    template<typename T>
    class SQLObject
    {
        public:
            SQLObject();
            
            bool loadFromBdd(const Query& query);

            static T* createFromBdd(const Query& query);
            static T* get(unsigned int id);
            static std::list<T*> filter();
            static std::list<T*> all();

            friend std::ostream& operator<<(std::ostream& output,const SQLObject& self)
            {
                for(VAttr* attr: self.attrs)
                    output<<*attr<<" ";
                return output;
            };

            static  Bdd* bdd_used;
        protected:
            int pk;
            const static std::string table;
            
            void registerAttr(VAttr& attr);

        private:
            friend class VAttr;
            std::vector<VAttr*> attrs;
    };
};

#define REGISTER_TABLE(T,tab) \
    template<>\
    const std::string orm::SQLObject<T>::table = tab;\
    template<>\
    orm::Bdd* orm::SQLObject<T>::bdd_used = &orm::Bdd::Default;

#define REGISTER_BDD(T,bdd) \
    orm::SQLObject<T>::bdd_used = bdd;

#include "SQLObject.tpl"
#endif
