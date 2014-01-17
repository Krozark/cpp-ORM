#include <ORM/backends/MySql/MySQLQuery.hpp>

#include <cppconn/exception.h>

namespace orm
{
    MySQLQuery::MySQLQuery(Bdd* bdd,const std::string& query) : Query(bdd,query), bdd_res(0), prepared_statement(0), statement(0)
    {
    };

    MySQLQuery::MySQLQuery(Bdd* bdd,std::string&& query) : Query(bdd,query), bdd_res(0), prepared_statement(0), statement(0)
    {
    };

    MySQLQuery::~MySQLQuery()
    {
        if(prepared and prepared_statement)
            delete prepared_statement;
        if(not prepared and statement)
            delete statement;
        if(bdd_res)
            delete bdd_res;
    };


    int MySQLQuery::count()const
    {
        return bdd_res->rowsCount();
    };

    bool MySQLQuery::get(bool& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getBoolean((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(int& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(unsigned int& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long long int& value,const int& column)const
    {    
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt64((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long long unsigned int& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt64((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(float& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = static_cast<float>(bdd_res->getDouble((uint32_t)column));
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(double& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getDouble((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long double& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getDouble((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(std::string& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getString((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::next()
    {
        return bdd_res->next();
    }

    bool MySQLQuery::set(const bool& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setBoolean(column,value);
        return true;
    };

    bool MySQLQuery::set(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt(column,value);
        return true;
    };

    bool MySQLQuery::set(const unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt(column,value);
        return true;
    };

    bool MySQLQuery::set(const long long int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt64(column,value);
        return true;
    };

    bool MySQLQuery::set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt64(column,value);
        return true;
    };

    bool MySQLQuery::set(const float& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,static_cast<double>(value));
        return true;
    };

    bool MySQLQuery::set(const double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,value);
        return true;
    };

    bool MySQLQuery::set(const long double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,value);
        return true;
    };

    bool MySQLQuery::set(const std::string& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setString(column,value);
        return true;
    };

    bool MySQLQuery::setNull(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setNull(column,sql::DataType::INTEGER);
        return true;
    };

    void MySQLQuery::executeQuery()
    {
        if(prepared)
            bdd_res = prepared_statement->executeQuery();
        else
            bdd_res = statement->executeQuery(query);
    };

};
