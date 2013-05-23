#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

#include "SQLObjectBase.hpp"


#include "VAttr.hpp" 


namespace orm
{
    class Bdd;
    class Query;

    template<typename T>
    class SQLObject : public SQLObjectBase
    {
        public:
            SQLObject();

            SQLObject(const SQLObject&) = delete;
            SQLObject& operator=(const SQLObject&) = delete;
            
            static T* createFromBdd(const Query& query);
            static T* get(unsigned int id);
            static std::list<T*> filter();
            static std::list<T*> all();

            virtual bool save(bool _new=false);

            static  Bdd* bdd_used;
        protected:
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

#include "SQLObject.tpl"
#endif
