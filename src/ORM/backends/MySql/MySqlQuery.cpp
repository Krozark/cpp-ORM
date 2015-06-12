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

    bool MySqlQuery::initResults()
    {
        prepared_results.clear();
        prepared_results.resize(num_fields_res);

        std::memset(prepared_results.data(), 0, sizeof(MYSQL_BIND)*num_fields_res);

        int i = 0;

        MYSQL_FIELD *field;
        while((field = mysql_fetch_field(db_res)))
        {
            prepared_results[i].buffer_type = field->type;
            switch(field->type)
            {
                case MYSQL_TYPE_DECIMAL:
                {
                    prepared_results[i].buffer = new double;
                    prepared_results[i].buffer_length = sizeof(double);
                }break;
                   /*MYSQL_TYPE_TINY,
			MYSQL_TYPE_SHORT,  MYSQL_TYPE_LONG,
			MYSQL_TYPE_FLOAT,  MYSQL_TYPE_DOUBLE,
			MYSQL_TYPE_NULL,   MYSQL_TYPE_TIMESTAMP,
			MYSQL_TYPE_LONGLONG,MYSQL_TYPE_INT24,
			MYSQL_TYPE_DATE,   MYSQL_TYPE_TIME,
			MYSQL_TYPE_DATETIME, MYSQL_TYPE_YEAR,
			MYSQL_TYPE_NEWDATE, MYSQL_TYPE_VARCHAR,
			MYSQL_TYPE_BIT,
			MYSQL_TYPE_TIMESTAMP2,
			MYSQL_TYPE_DATETIME2,
			MYSQL_TYPE_TIME2,
                        MYSQL_TYPE_NEWDECIMAL=246,
			MYSQL_TYPE_ENUM=247,
			MYSQL_TYPE_SET=248,
			MYSQL_TYPE_TINY_BLOB=249,
			MYSQL_TYPE_MEDIUM_BLOB=250,
			MYSQL_TYPE_LONG_BLOB=251,
			MYSQL_TYPE_BLOB=252,
			MYSQL_TYPE_VAR_STRING=253,
			MYSQL_TYPE_STRING=254,
			MYSQL_TYPE_GEOMETRY=255*/

            }
            //unsigned long max_length;   /* Max width for selected set */
            //enum enum_field_types type; /* Type of field. See mysql_com.h for types */

            ++i;
        }

        return (i == num_fields_res);
    }

};
