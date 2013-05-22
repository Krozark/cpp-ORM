#include <algorithm>

#include "Query.hpp"

namespace orm
{
    Query::Query(Bdd* b) : bdd(b), executed(false)
    {
    };

    Query::Query(Bdd* b,const std::string& q) : bdd(b),query(q), executed(false)
    {
    };

    Query::Query(Bdd* b,std::string&& q) : bdd(b), executed(false)
    {
        std::swap(q,query);
    };

    Query& Query::limit(const unsigned int& l)
    {
        query += " LIMIT "+std::to_string(l);
    };

    bool Query::execute()
    {
        executed = true;
        return bdd->executeQuery(*this);
    };

    /*std::ostream& operator<<(std::ostream& output,const Query& self)
    {
        output<<self.query;
        return output;
    };*/
    
};
