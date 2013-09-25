#include <algorithm>

#include <ORM/backends/Query.hpp>


namespace orm
{
    Query::Query(Bdd* b,const std::string& q) : bdd(b),query(q), executed(false), prepared(false)
    {
    };

    Query::Query(Bdd* b,std::string&& q) : bdd(b), executed(false), prepared(false)
    {
        std::swap(q,query);
    };

    Query::~Query()
    {
    }

    /*Query& Query::limit(const unsigned int& l)
    {
        query += " LIMIT "+std::to_string(l);
    };*/


    bool Query::execute()
    {
        executed = true;
        if(not prepared)
        {
            query+=";";
        }
        return executeQuery();
    };

};
