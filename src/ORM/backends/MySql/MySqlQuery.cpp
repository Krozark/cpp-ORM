#include <ORM/backends/MySql/MySqlQuery.hpp>
#include <ORM/backends/MySql/MySqlDB.hpp>

//#include <cppconn/exception.h>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cassert>

namespace orm
{
    MySqlQuery::MySqlQuery(DB& db,const std::string& query) : Query(db,query), db_res(nullptr), current_res(nullptr), prepared_statement(nullptr)
    {
        //remove all ';' at the end 
        auto s = query.size() -1;

        while(s >= 0 and query[s] == ';')
            --s;
        if(s != query.size() - 1)
            Query::query = Query::query.substr(0,s + 1);

        std::cout<<JAUNE<<Query::query<<BLANC<<std::endl;
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


        for(MYSQL_BIND& param : prepared_params)
        {
            switch(param.buffer_type)
            {
                case MYSQL_TYPE_TINY :
                {
                    delete reinterpret_cast<bool*>(param.buffer);
                }break;
                case MYSQL_TYPE_LONG :
                {
                    if(param.is_unsigned)
                        delete reinterpret_cast<unsigned int*>(param.buffer);
                    else
                        delete reinterpret_cast<int*>(param.buffer);
                }break;
                case MYSQL_TYPE_LONGLONG :
                {
                    if(param.is_unsigned)
                        delete reinterpret_cast<long long unsigned int*>(param.buffer);
                    else
                        delete reinterpret_cast<long long int*>(param.buffer);
                }break;
                case MYSQL_TYPE_FLOAT:
                {
                    delete reinterpret_cast<float*>(param.buffer);
                }break;
                case MYSQL_TYPE_DOUBLE:
                {
                    delete reinterpret_cast<double*>(param.buffer);
                }break;
                case MYSQL_TYPE_STRING:
                {
                    delete[] reinterpret_cast<char*>(param.buffer);
                }break;
                default:
                {
                    std::cerr<<ROUGE<<"??? MySqlQuery::~MySqlQuery() : Type "<<param.buffer_type<<" not bind"<<BLANC<<std::endl;
                    assert(false && "This case should never apear");
                }

            }
        }

        #error prepared_results

    };


    int MySqlQuery::count()const
    {
        if(prepared)
            return mysql_stmt_num_rows(prepared_statement);
        else
            return mysql_num_rows(db_res);
    };

    bool MySqlQuery::get(bool& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_TINY);

            value = *reinterpret_cast<bool*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::get(int& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_LONG);

            value = *reinterpret_cast<int*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::getPk(int& value, const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_LONG);

            if (prepared_results[column].is_null)
            {
                value = -1;
                return false;
            }

            value = *reinterpret_cast<unsigned int*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    }

    bool MySqlQuery::get(unsigned int& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_LONG);

            value = *reinterpret_cast<unsigned int*>(prepared_results[column].buffer);

            return true;
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }
    };

    bool MySqlQuery::get(long long int& value,const int& column)const
    {    
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_LONGLONG);

            value = *reinterpret_cast<long long int*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::get(long long unsigned int& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_LONGLONG);

            value = *reinterpret_cast<long long unsigned int*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::get(float& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_FLOAT);

            value = *reinterpret_cast<float*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::get(double& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_DOUBLE);

            value = *reinterpret_cast<double*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::get(long double& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_DOUBLE);

            value = *reinterpret_cast<double*>(prepared_results[column].buffer);
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return true;
    };

    bool MySqlQuery::get(std::string& value,const int& column)const
    {
        if(prepared)
        {
            assert(column < int(prepared_results.size()));
            assert(prepared_results[column].buffer_type == MYSQL_TYPE_STRING);

          /*data= malloc(real_length);
  bind[0].buffer= data;
  bind[0].buffer_length= real_length;
  mysql_stmt_fetch_column(stmt, bind, 0, 0);*/

        #error todo allocate the buffer

            value = *reinterpret_cast<char*>(prepared_results[column].buffer);
        }
        else
        {
            value = current_res[column];
        }
        
        return true;
    };
    
    bool MySqlQuery::get(struct tm& value,const int& column)const
    {
        bool res;

        std::string str;
        res = get(str,column);
        if(res)
        {
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
        }
        return res;
    }

    bool MySqlQuery::next()
    {
        if(prepared)
        {
            mysql_stmt_fetch(prepared_statement);
        }
        else
        {
            if(db_res)
                current_res = mysql_fetch_row(db_res);
            return (current_res != nullptr);
        }
        return false;
    }

    bool MySqlQuery::set(const bool& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_TINY;
        prepared_params[column].buffer = new bool(value);
        prepared_params[column].buffer_length = sizeof(bool);
        prepared_params[column].length = &(prepared_params[column].buffer_length);

        return true;
    };

    bool MySqlQuery::set(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_LONG;
        prepared_params[column].buffer = new int(value);
        prepared_params[column].buffer_length = sizeof(int);
        prepared_params[column].length = &(prepared_params[column].buffer_length);

        return true;
    };

    bool MySqlQuery::set(const unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_LONG;
        prepared_params[column].buffer = new unsigned int(value);
        prepared_params[column].buffer_length = sizeof(unsigned int);
        prepared_params[column].length = &(prepared_params[column].buffer_length);
        prepared_params[column].is_unsigned = true;

        return true;
    };

    bool MySqlQuery::set(const long long int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_LONGLONG;
        prepared_params[column].buffer = new long long int(value);
        prepared_params[column].buffer_length = sizeof(long long int);
        prepared_params[column].length = &(prepared_params[column].buffer_length);
        return true;
    };

    bool MySqlQuery::set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_LONGLONG;
        prepared_params[column].buffer = new long long unsigned int(value);
        prepared_params[column].buffer_length = sizeof(long long unsigned int);
        prepared_params[column].length = &(prepared_params[column].buffer_length);
        prepared_params[column].is_unsigned = true;

        return true;
    };

    bool MySqlQuery::set(const float& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_FLOAT;
        prepared_params[column].buffer = new float(value);
        prepared_params[column].buffer_length = sizeof(float);
        prepared_params[column].length = &(prepared_params[column].buffer_length);

        return true;
    };

    bool MySqlQuery::set(const double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_DOUBLE;
        prepared_params[column].buffer = new double(value);
        prepared_params[column].buffer_length = sizeof(double);
        prepared_params[column].length = &(prepared_params[column].buffer_length);

        return true;
    };

    bool MySqlQuery::set(const long double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_DOUBLE;
        prepared_params[column].buffer = new double(value);
        prepared_params[column].buffer_length = sizeof(double);
        prepared_params[column].length = &(prepared_params[column].buffer_length);

        return true;
    };

    bool MySqlQuery::set(const std::string& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        const int size = value.size();
        char* buffer = new char[value.size()+1];
        memcpy(buffer,value.c_str(),size);

        prepared_params[column].buffer_type = MYSQL_TYPE_STRING;
        prepared_params[column].buffer = buffer;
        prepared_params[column].buffer_length = size;
        prepared_params[column].is_null_value = false;
        prepared_params[column].is_null = &(prepared_params[column].is_null_value);
        prepared_params[column].length = &(prepared_params[column].buffer_length);

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

        return set(stream.str(),column);
    }

    bool MySqlQuery::setNull(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;

        _resizePreparedParams(column);

        prepared_params[column].buffer_type = MYSQL_TYPE_LONG;
        prepared_params[column].buffer = new int(value);
        prepared_params[column].buffer_length = sizeof(int);
        prepared_params[column].length = &(prepared_params[column].buffer_length);
        prepared_params[column].is_null_value = true;
        prepared_params[column].is_null = &(prepared_params[column].is_null_value);

        return true;
    };

    void MySqlQuery::executeQuery()
    {
        std::cout<<query.c_str()<<" prepared? "<<prepared<<std::endl;

        if(prepared)
        {
            if(mysql_stmt_prepare(prepared_statement,query.c_str(),query.size()))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : Could not execute the query. Error message:"<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            //bool b = true;
            //mysql_stmt_attr_set(prepared_statement, STMT_ATTR_UPDATE_MAX_LENGTH,&b); //Setting the STMT_ATTR_UPDATE_MAX_LENGTH attribute causes the maximal length of column values to be indicated by the max_length member of the result set metadata returned by mysql_stmt_result_metadata().
            db_res = mysql_stmt_result_metadata(prepared_statement);

            std::cout<<JAUNE<<"executeQuery()"<<BLANC<<std::endl;
            if(db_res != nullptr)
            {

                std::cout<<VERT<<"executeQuery()"<<BLANC<<std::endl;

                int num_fields_res = mysql_num_fields(db_res);
                if(!_initResults(num_fields_res))
                {
                    std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : Could not execute prepare the results"<<BLANC<<std::endl;
                    return;
                }
                //mysql_stmt_store_result()
            }

            if(mysql_stmt_bind_param(prepared_statement,prepared_params.data()))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : mysql_stmt_bind_param failed"<<BLANC<<std::endl;
                return;
            }

            if(mysql_stmt_execute(prepared_statement))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : mysql_stmt_execute(), failed. Error messuge: "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            mysql_stmt_bind_result(prepared_statement,prepared_results.data());
            mysql_stmt_store_result(prepared_statement);

        }
        else
        {
            MYSQL* con = dynamic_cast<MySqlDB*>(&db)->dbConn;

            if(mysql_query(con,query.c_str()))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : Could not execute the query. Error message:"<<mysql_error(con)<<BLANC<<std::endl;
                return;
            }

            db_res = mysql_store_result(con);
            if(db_res == nullptr)
            {
                if(mysql_errno(con)) // mysql_store_result() returned nothing; should it have?
                {
                    // query should return data
                    // (it was a SELECT)
                    std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : Could not get query results. Error message:"<<mysql_error(con)<<BLANC<<std::endl;
                }
                return;
            }
            //num_fields_res = mysql_num_fields(db_res);

        }

    };

    bool MySqlQuery::_initResults(int num_fields_res)
    {

        #error TODO

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
                case MYSQL_TYPE_TINY :
                {
                    prepared_results[i].buffer = new bool(0);
                    prepared_results[i].buffer_length = sizeof(bool);
                    prepared_results[i].length = &(prepared_results[i].buffer_length);
                }break;

                case MYSQL_TYPE_LONG :
                {
                    prepared_results[i].buffer = new int(0);
                    prepared_results[i].buffer_length = sizeof(int);
                    prepared_results[i].length = &(prepared_results[i].buffer_length);

                }break;

                case MYSQL_TYPE_LONGLONG :
                {
                    prepared_results[i].buffer = new long long int(0);
                    prepared_results[i].buffer_length = sizeof(long long int);
                    prepared_results[i].length = &(prepared_results[i].buffer_length);
                }break;

                case MYSQL_TYPE_FLOAT:
                {
                    prepared_results[i].buffer = new float(0);
                    prepared_results[i].buffer_length = sizeof(float);
                    prepared_results[i].length = &(prepared_results[i].buffer_length);
                }break;

                case MYSQL_TYPE_DOUBLE:
                {
                    prepared_results[i].buffer = new double(0);
                    prepared_results[i].buffer_length = sizeof(double);
                    prepared_results[i].length = &(prepared_results[i].buffer_length);
                }break;

                case MYSQL_TYPE_VAR_STRING:
                case MYSQL_TYPE_STRING:
                {
                    prepared_results[i].buffer = 0;
                    prepared_results[i].buffer_length = 0;
                    prepared_results[i].length = &(prepared_results[i].buffer_length);
                }break;

                default :
                {
                    std::cerr<<ROUGE<<"MySqlQuery::_initResults : Type "<<field->type<<" not bind"<<BLANC<<std::endl;
                    assert(false && "This case should never apear");
                }

            /*
			MYSQL_TYPE_NULL,   MYSQL_TYPE_TIMESTAMP,
                ,MYSQL_TYPE_INT24,
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
			MYSQL_TYPE_GEOMETRY=255*/

            }
            //unsigned long max_length;   /* Max width for selected set */
            //enum enum_field_types type; /* Type of field. See mysql_com.h for types */

            ++i;
        }

        return (i == num_fields_res);
    }

    void MySqlQuery::_resizePreparedParams(unsigned int s)
    {
        unsigned int size = prepared_params.size();
        if(size < ++s)
        {
            MYSQL_BIND n;
            memset(&n,0,sizeof(MYSQL_BIND));
            prepared_params.resize(s,n);
        }
    }

};
