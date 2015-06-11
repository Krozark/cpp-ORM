#include <ORM/backends/MySql/MySqlQuery.hpp>

//#include <cppconn/exception.h>
#include <sstream>
#include <iomanip>

namespace orm
{
    MySqlQuery::MySqlQuery(DB& db,const std::string& query) : Query(db,query), db_res(nullptr), current_res(nullptr), num_fields_res(0),prepared_statement(nullptr)
    {
        //remove all ';' at the end 
        auto s = query.size() -1;
        while(s >= 0 and query[s] == ';')
            --s;
        if(s != query.size() - 1)
            Query::query = Query::query.substr(0,s);
    };

    MySqlQuery::~MySqlQuery()
    {
        if(prepared and prepared_statement)
        {
            mysql_stmt_close(prepared_statement);
            prepared_statement = nullptr;
        }

        if(db_res)
        {
            mysql_free_result(db_res);
        }
    };


    int MySqlQuery::count()const
    {
        if(prepared)
            return mysql_stmt_num_row(prepared_statement);
        else
            return mysql_num_rows(db_res);
    };

    bool MySqlQuery::get(bool& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getBoolean((uint32_t)column);
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
            value = db_res->getInt((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::getPk(int& value, const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            if(db_res->isNull((uint32_t)column))
            {
                value = -1;
                return false;
            }
            value = db_res->getUInt((uint32_t)column);
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
            value = db_res->getUInt((uint32_t)column);
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
            value = db_res->getInt64((uint32_t)column);
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
            value = db_res->getUInt64((uint32_t)column);
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
            value = static_cast<float>(db_res->getDouble((uint32_t)column));
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
            value = db_res->getDouble((uint32_t)column);
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
            value = db_res->getDouble((uint32_t)column);
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
            value = db_res->getString((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };
    
    bool MySqlQuery::get(struct tm& value,const int& column)const
    {
        bool res;
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            std::string str;
            str = db_res->getString((uint32_t)column);

            int year,mon,day,hour,min,sec;
            res = ::sscanf(str.c_str(),"%4d-%2d-%2d %2d:%2d:%2d",&year,&mon,&day,&hour,&min,&sec) == 6;
            if (res)
            {
                value.tm_year = year;
                value.tm_mon = mon;
                value.tm_mday = day;
                value.tm_hour = hour;
                value.tm_min = min;
                value.tm_sec = sec;
            }
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            res = false;
        }
        #endif

        return res;
    }

    bool MySqlQuery::next()
    {
        if(prepared)
        {
            #error TODO
        }
        else
        {
            current_res = mysql_fetch_row(db_res);
            return (current_res != nullptr);
        }
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

    bool MySqlQuery::set(const struct tm& value, const unsigned int& column)
    {
        if(not prepared)
            return false;

        std::stringstream stream;
        stream<<std::setfill('0')
            <<std::setw(4)<<value.tm_year
            <<"-"<<std::setw(2)<<value.tm_mon
            <<"-"<<std::setw(2)<<value.tm_mday
            <<" "
            <<std::setw(2)<<value.tm_hour
            <<":"<<std::setw(2)<<value.tm_min
            <<":"<<std::setw(2)<<value.tm_sec;

        prepared_statement->setString(column,stream.str());
        return true;
    }

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
        {
            if(mysql_stmt_prepare(prepared_statement,query.c_str(),query.size()))
            {
                std::cerr<"Could not execute the query. Error message:"<<mysql_stmt_error(prepared_statement)<<std::endl;
                return;
            }

            if(mysql_stmt_bind_param(prepared_statement,prepared_params.data()))
            {
                std::cerr<<"mysql_stmt_bind_param failed"<<std::endl;
                return;
            }

            if(mysql_stmt_execute(prepared_statement))
            {
                std::cerr<<"mysql_stmt_execute(), failed. Error messuge: "<<mysql_stmt_error(statement)<<std:endl;
                return;
            }

            db_res = mysql_stmt_result_metadata(prepared_statement);
            num_fields_res = mysql_num_fields(bd_res);


        }
        else
        {
            MYSQL* con = static_cast<MySqlQuery&>(Query::db)->dbConn;
            if(mysql_query(conn,query.c_str()))
            {
                std::cerr<"Could not execute the query. Error message:"<<mysql_error(con)<<std::endl;
                return;
            }

            bd_res = mysql_store_result(con);
            if(bd_res == nullptr)
            {
                std::cerr<"Could not get query results. Error message:"<<mysql_error(con)<<std::endl;
                return;
            }

            num_fields_res = mysql_num_fields(bd_res);
        }

    };

};
