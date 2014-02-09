#include <ORM/backends/MySql/MySqlQuery.hpp>

#include <cppconn/exception.h>

namespace orm
{
    MySqlQuery::MySqlQuery(Bdd& bdd,const std::string& query) : Query(bdd,query), bdd_res(0), prepared_statement(0), statement(0)
    {
    };

    MySqlQuery::MySqlQuery(Bdd& bdd,std::string&& query) : Query(bdd,query), bdd_res(0), prepared_statement(0), statement(0)
    {
    };

    MySqlQuery::~MySqlQuery()
    {
        if(prepared and prepared_statement)
            delete prepared_statement;
        if(not prepared and statement)
            delete statement;
        if(bdd_res)
            delete bdd_res;
    };


    int MySqlQuery::count()const
    {
        return bdd_res->rowsCount();
    };

    bool MySqlQuery::get(bool& value,const int& column)const
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

    bool MySqlQuery::get(int& value,const int& column)const
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

    bool MySqlQuery::getPk(int& value, const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            if(bdd_res->isNull((uint32_t)colum))
            {
                value = -1;
                return false;
            }
            value = bdd_res->getUInt((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            value = -1;
            return false;
        }
        #endif
        return true;
    }

    bool MySqlQuery::get(unsigned int& value,const int& column)const
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

    bool MySqlQuery::get(long long int& value,const int& column)const
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

    bool MySqlQuery::get(long long unsigned int& value,const int& column)const
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

    bool MySqlQuery::get(float& value,const int& column)const
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

    bool MySqlQuery::get(double& value,const int& column)const
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

    bool MySqlQuery::get(long double& value,const int& column)const
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

    bool MySqlQuery::get(std::string& value,const int& column)const
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

    bool MySqlQuery::next()
    {
        return bdd_res->next();
    }

    bool MySqlQuery::set(const bool& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setBoolean(column,value);
        return true;
    };

    bool MySqlQuery::set(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt(column,value);
        return true;
    };

    bool MySqlQuery::set(const unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt(column,value);
        return true;
    };

    bool MySqlQuery::set(const long long int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt64(column,value);
        return true;
    };

    bool MySqlQuery::set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt64(column,value);
        return true;
    };

    bool MySqlQuery::set(const float& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,static_cast<double>(value));
        return true;
    };

    bool MySqlQuery::set(const double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,value);
        return true;
    };

    bool MySqlQuery::set(const long double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,value);
        return true;
    };

    bool MySqlQuery::set(const std::string& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setString(column,value);
        return true;
    };

    bool MySqlQuery::setNull(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setNull(column,sql::DataType::INTEGER);
        return true;
    };

    void MySqlQuery::executeQuery()
    {
        if(prepared)
            bdd_res = prepared_statement->executeQuery();
        else
            bdd_res = statement->executeQuery(query);
    };

};