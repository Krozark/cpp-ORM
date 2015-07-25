#include <ORM/backends/MySql/MySqlQuery.hpp>
#include <ORM/backends/MySql/MySqlDB.hpp>

//#include <cppconn/exception.h>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cassert>

namespace orm
{
    MySqlQuery::MySqlQuery(DB& db,const std::string& query) : Query(db,query), db_res(nullptr), current_res(nullptr), num_fields_res(0), prepared_statement(nullptr)
    {
        //remove all ';' at the end 
        auto s = query.size() -1;

        while(s >= 0 and query[s] == ';')
            --s;
        if(s != query.size() - 1)
            Query::query = Query::query.substr(0,s + 1);
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

        //#error prepared_results

    };


    int MySqlQuery::count()const
    {
        if(prepared)
            return mysql_stmt_num_rows(prepared_statement);
        else
            return mysql_num_rows(db_res);
    };

    /*template<typename T>
    bool MySqlQuery::_getValue(T& value,const int& column)
    {
        bool res = true;
        if(prepared)
        {
            assert(column < int(prepared_results.size()));

            if(prepared_results_buffer.is_null)
            {
                value = T();
                res = false;
            }
            else
            {
                int len = prepared_results_buffer[column].real_len;

                prepared_results_buffer[column].buffer[real_len + 1] = '\0';

                std::stringstream(prepared_results_buffer[column].buffer) >> value;
            }
            
        }
        else
        {
            std::stringstream(current_res[column]) >> value;
        }

        return res;
    }*/

    bool MySqlQuery::get(bool& value,const int& column)const
    {
        //return _getValue(value,column);
    };

    bool MySqlQuery::get(int& value,const int& column)const
    {
        //return _getValue(value,column);
    };

    bool MySqlQuery::getPk(int& value, const int& column)const
    {
       /* if(not _getValue(value,column))
        {
            value = -1;
        }*/
    }

    bool MySqlQuery::get(unsigned int& value,const int& column)const
    {
       // return _getValue(value,column);
    };

    bool MySqlQuery::get(long long int& value,const int& column)const
    {    
        //return _getValue(value,column);
    };

    bool MySqlQuery::get(long long unsigned int& value,const int& column)const
    {
        //return _getValue(value,column);
    };

    bool MySqlQuery::get(float& value,const int& column)const
    {
        //return _getValue(value,column);
    };

    bool MySqlQuery::get(double& value,const int& column)const
    {
        //return _getValue(value,column);
    };

    bool MySqlQuery::get(long double& value,const int& column)const
    {
        //return _getValue(value,column);
    };

    bool MySqlQuery::get(std::string& value,const int& column)const
    {
        //return _getValue(value,column);
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
        bool res = true;
        if(prepared)
        {
            if(num_fields_res > 0)
            {
                res = mysql_stmt_fetch(prepared_statement);
                if(res == 1)
                {
                    std::cerr<<ROUGE<<"MySqlQuery::next() Error : "<<mysql_stmt_errno(prepared_statement)<<" : "<<               mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                }
                else if (res == MYSQL_NO_DATA)
                {
                    std::cerr<<ROUGE<<"MySqlQuery::next() MYSQL_NO_DATA : "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                }
                else if (res == MYSQL_DATA_TRUNCATED)
                {
                    std::cerr<<ROUGE<<"MySqlQuery::next() MYSQL_DATA_TRUNCATED : "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                }

                res = not res;
                std::cout<<JAUNE<<"next: "<<res<<BLANC<<std::endl;
            }

        }
        else
        {
            if(db_res)
                current_res = mysql_fetch_row(db_res);
            res =  (current_res != nullptr);
        }
        return res;
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
        prepared_params[column].buffer_length = size + 1;
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
        if(prepared)
        {
            {
                MYSQL* con = dynamic_cast<MySqlDB*>(&db)->dbConn;
                prepared_statement = mysql_stmt_init(con);
                if(prepared_statement == nullptr)
                {
                    std::cerr<<"MySqlQuery::executeQuery() mysql_stmt_init(): Could not create the statement. Error message : "<< mysql_error(con) <<std::endl;
                    return;
                }
            }

            if(mysql_stmt_prepare(prepared_statement,query.c_str(),query.size() + 1))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() mysql_stmt_prepare() : Could not execute the query. Error message:"<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            std::cout<<"prepared_params.size(): "<<prepared_params.size()<<std::endl;

            if(mysql_stmt_bind_param(prepared_statement,prepared_params.data()))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() mysql_stmt_bind_param() "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            db_res = mysql_stmt_result_metadata(prepared_statement);

            if(db_res == nullptr)
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() mysql_stmt_result_metadata() : db_res == nullptr. Error: "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            {//for results length
                my_bool arg = 1;
                if(mysql_stmt_attr_set(prepared_statement,STMT_ATTR_UPDATE_MAX_LENGTH,&arg))
                {
                    std::cerr<<ROUGE<<"MySqlQuery::executeQuery() mysql_stmt_attr_set Error:"<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                    return;
                }
            }


            if(mysql_stmt_execute(prepared_statement))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : mysql_stmt_execute(), failed. Error messuge: "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            if (mysql_stmt_store_result(stmt) != 0)
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() : mysql_stmt_store_result(), failed. Error messuge: "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            num_fields_res = mysql_num_fields(db_res);
            std::cout<<JAUNE<<"num_fields_res: "<<num_fields_res<<BLANC<<std::endl;
            
            if(!_initResults())
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() _initResults() : Could not execute prepare the results"<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }

            if(mysql_stmt_bind_result(prepared_statement,prepared_results.data()))
            {
                std::cerr<<ROUGE<<"MySqlQuery::executeQuery() mysql_stmt_bind_result() : "<<mysql_stmt_error(prepared_statement)<<BLANC<<std::endl;
                return;
            }
            
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

    }

    bool MySqlQuery::_initResults()
    {

        prepared_results.clear();
        prepared_results.resize(num_fields_res);
        std::memset(prepared_results.data(), 0, sizeof(MYSQL_BIND)*num_fields_res);

        prepared_results_buffer.clear();
        prepared_results_buffer.resize(num_fields_res);


        for(int i = 0;i< num_fields_res;++i)
        {
            MYSQL_FIELD* field = &(db_res->fields[i]);

            prepared_results_buffer[i].buffer.resize(field->max_length + 1,'\0');

            prepared_results[i].buffer_type = MYSQL_TYPE_STRING;
            prepared_results[i].buffer = &(prepared_results_buffer[i][0]);
            prepared_results[i].buffer_length = field->max_length;
            prepared_results[i].is_null = &prepared_results_buffer[i].is_null;
            prepared_results[i].length = &(prepared_results_buffer[i].real_len);
        }

        return true;
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
