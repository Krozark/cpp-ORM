#include "MySQLQuery.hpp"

namespace orm
{
    MySQLQuery::MySQLQuery(Bdd* bdd) : Query(bdd), bdd_res(0)
    {
    };

    MySQLQuery::MySQLQuery(Bdd* bdd,const std::string& query) : Query(bdd,query), bdd_res(0)
    {
    };

    MySQLQuery::MySQLQuery(Bdd* bdd,std::string&& query) : Query(bdd,query), bdd_res(0)
    {
    };

    MySQLQuery::~MySQLQuery()
    {
        if(bdd_res)
            delete bdd_res;
    };

    MySQLQuery& MySQLQuery::orderBy(const std::string& colum,char order)
    {
        return *this;
    };

    MySQLQuery& MySQLQuery::join(const std::string& colum,const Query& other)
    {
        return *this;
    };

    bool MySQLQuery::next()
    {
        return bdd_res->next();
    }

    
    
};
