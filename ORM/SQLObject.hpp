#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

#include "Query.hpp"
#include "Bdd.hpp"

#include <list>

#include <iostream>

namespace orm
{
    template<typename T>
    class SQLObject
    {
        public:
            SQLObject() : pk(-1)
            {
            };

            bool loadFromBdd(Query& query)
            {
                return true;
            };

            T createFromBdd(Query& query) const 
            {
                return SQLObject();
            };

            static T* get(unsigned int id)
            {
                Query* q = bdd_used->query("SELECT * FROM "+table+" WHERE id "+(*bdd_used)["exact"]+std::to_string(id)+";");
                std::cerr<<(q)<<std::endl;
                return 0;
            };
            static std::list<T*> filter();
            static std::list<T*> all();

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
