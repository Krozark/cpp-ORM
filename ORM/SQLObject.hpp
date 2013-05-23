#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

#include "Bdd.hpp"
#include "Query.hpp"

#include <list>


namespace orm
{
    class Query;

    template<typename T>
    class SQLObject
    {
        public:
            SQLObject() : pk(-1)
            {
            };

            bool loadFromBdd(Query& query)
            {
                //TODO Loop on this->attrs
                return true;
            };

            static T* createFromBdd(Query& query)
            {
                //TODO Loop on this->attrs
                T* res = new T;
                return res;
            };

            static T* get(unsigned int id)
            {
                Query* q = bdd_used->query("SELECT * FROM "+
                                           table+
                                           " WHERE (id "+
                                           (*bdd_used)["exact"]+std::to_string(id)+
                                           ") ");
                return createFromBdd(*q);
            };
            static std::list<T*> filter();

            static std::list<T*> all()
            {
               /* Query* q = bdd_used->query("SELECT * FROM "+table+" ");
                q->execute();*/
            };

            static  Bdd* bdd_used;
        protected:
            int pk;
            const static std::string table;
    };
};

#define REGISTER_TABLE(T,tab) \
    template<>\
    const std::string orm::SQLObject<T>::table = tab;\
    template<>\
    orm::Bdd* orm::SQLObject<T>::bdd_used = &orm::Bdd::Default;

#define REGISTER_BDD(T,bdd) \
    orm::SQLObject<T>::bdd_used = bdd;


#endif
