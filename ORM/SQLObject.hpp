#include "Query.hpp"

#include <list>

namespace orm
{
    template<class T>
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

            SQLObject createFromBdd(Query& query) const 
            {
                return SQLObject();
            };

            /*static SQLObject* get(unsigned int id) = 0;
            static std::list<SQLObject*> filter() = 0;
            static std::list<SQLObject*> all() = 0;*/

        protected:
            int pk;
            static  bdd::Bdd* bdd_used;
            const static std::string table;
    };
};
