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

    MySQLQuery& MySQLQuery::limit(const int& skip,const int& count)
    {
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(skip)+" , "+std::to_string(count);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        else
            std::cerr<<ROUGE<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        return *this;
    };

    int MySQLQuery::count()const
    {
        return bdd_res->rowsCount();
    };

    bool MySQLQuery::get(bool& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getBoolean((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(int& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(unsigned int& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long long int& value,const int& colum)const
    {    
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt64((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long long unsigned int& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt64((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(float& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = static_cast<float>(bdd_res->getDouble((uint32_t)colum));
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long double& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getDouble((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(std::string& value,const int& colum)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getString((uint32_t)colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    //std::istream * getBlob

    bool MySQLQuery::next()
    {
        return bdd_res->next();
    }

    bool MySQLQuery::set(const bool& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setBoolean(colum,value);
        return true;
    };

    bool MySQLQuery::set(const int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt(colum,value);
        return true;
    };

    bool MySQLQuery::set(const unsigned int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt(colum,value);
        return true;
    };

    bool MySQLQuery::set(const long long int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt64(colum,value);
        return true;
    };

    bool MySQLQuery::set(const long long unsigned int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt64(colum,value);
        return true;
    };

    bool MySQLQuery::set(const float& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(colum,static_cast<double>(value));
        return true;
    };

    bool MySQLQuery::set(const long double& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(colum,value);
        return true;
    };

    bool MySQLQuery::set(const std::string& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setString(colum,value);
        return true;
    };

    bool MySQLQuery::setNull(const int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        prepared_statement->setNull(colum,sql::DataType::INTEGER);
        return true;
    };

    bool MySQLQuery::executeQuery()
    {
        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<"\033[32m"<<query<<"\033[00m"<<std::endl;
        #endif
        if(prepared)
        {
            bdd_res = 0;
            return prepared_statement->execute();
        }
        else
        {
            bdd_res = statement->executeQuery(query);
            return true;
        }
    };

};
