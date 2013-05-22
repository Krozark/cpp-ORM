#include "Query.hpp"
#include "Bdd.hpp"

#include <list>

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

            SQLObject createFromBdd(Query& query) const 
            {
                return SQLObject();
            };

            static T* get(unsigned int id);
            static std::list<T*> filter();
            static std::list<T*> all();

        protected:
            int pk;
            static  Bdd* bdd_used;
            const static std::string table;
    };
};
