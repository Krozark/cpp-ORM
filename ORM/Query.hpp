#ifndef ORM_QUERY_HPP
#define ORM_QUERY_HPP

#include "Bdd.hpp"
#include "SQLObject.hpp"

#include <string>
#include <list>
#include <ostream>

namespace orm
{
    class Bdd;

    class Query
    {
        public:
            Query(Bdd* bdd);
            Query(Bdd* bdd,const std::string& query);
            Query(Bdd* bdd,std::string&& query);

            Query(const Query&) = delete;
            Query& operator=(const Query&) = delete;

            virtual Query& orderBy(const std::string& colum,char order='+') = 0;
            virtual Query& limit(const unsigned int& limit);
            virtual Query& join(const std::string& colum,const Query& other) = 0;

            /* construct objects from the query result and the number of object created */
            template<typename T>
            int getObj(SQLObject<T>& obj);

            template<typename T>
            int getObj(const SQLObject<T>& base,std::list<SQLObject<T> >& objs);

            friend std::ostream& operator<<(std::ostream& output,const Query& self);

        protected:
            friend class Bdd;
            /* query as string */
            std::string query;
            /* where to execute the query */
            Bdd* bdd;
    
            /* whene the query have been execute, for parse each raw */
            virtual bool next() = 0;

        private:
            bool execute();
            bool executed;
    };
};
#include "Query.tpl"

#endif
