#include <ORM/backends/MySql/MySQLQuery.hpp>

#include <cppconn/exception.h>

namespace orm
{
    MySQLQuery::MySQLQuery(Bdd* bdd) : Query(bdd), bdd_res(0), prepared_statement(0)
    {
    };

    MySQLQuery::MySQLQuery(Bdd* bdd,const std::string& query) : Query(bdd,query), bdd_res(0), prepared_statement(0)
    {
    };

    MySQLQuery::MySQLQuery(Bdd* bdd,std::string&& query) : Query(bdd,query), bdd_res(0), prepared_statement(0)
    {
    };

    MySQLQuery::~MySQLQuery()
    {
        if(prepared and prepared_statement)
            delete prepared_statement;
        if(bdd_res)
            delete bdd_res;
    };

    /*MySQLQuery& MySQLQuery::orderBy(const std::string& colum,char order)
    {
        return *this;
    };

    MySQLQuery& MySQLQuery::join(const std::string& colum,const Query& other)
    {
        return *this;
    };*/

    int MySQLQuery::count()const
    {
        return bdd_res->rowsCount();
    };

    bool MySQLQuery::get(bool& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getBoolean(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(int& value,const std::string& colum)const
    {

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(unsigned int& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long long int& value,const std::string& colum)const
    {    
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt64(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long long unsigned int& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt64(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(float& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = static_cast<float>(bdd_res->getDouble(colum));
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(long double& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getDouble(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySQLQuery::get(std::string& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getString(colum);
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
};
