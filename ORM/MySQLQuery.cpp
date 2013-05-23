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

    int MySQLQuery::count()const
    {
        return bdd_res->rowsCount();
    };

    bool MySQLQuery::get(bool& value,const std::string colum)const
    {
        value = bdd_res->getBoolean(colum);
    };

    bool MySQLQuery::get(int& value,const std::string colum)const
    {
        value = bdd_res->getInt(colum);
    };

    bool MySQLQuery::get(unsigned int& value,const std::string colum)const
    {
        value = bdd_res->getUInt(colum);
    };

    bool MySQLQuery::get(long long int& value,const std::string colum)const
    {    
        value = bdd_res->getInt64(colum);
    };

    bool MySQLQuery::get(long long unsigned int& value,const std::string colum)const
    {
        value = bdd_res->getUInt64(colum);
    };

    bool MySQLQuery::get(float& value,const std::string colum)const
    {
        value = static_cast<float>(bdd_res->getDouble(colum));
    };

    //long double getDouble
    bool MySQLQuery::get(long double& value,const std::string colum)const
    {
        value = bdd_res->getDouble(colum);
    };

    bool MySQLQuery::get(std::string& value,const std::string colum)const
    {
        value = bdd_res->getString(colum);
    };





    //std::istream * getBlob
    //int64_t getInt64

    bool MySQLQuery::next()
    {
        return bdd_res->next();
    }

    
    
};
