#include <ORM/backends/MySql/MySqlQuery.hpp>
#include <ORM/backends/MySql/MySqlDB.hpp>

//#include <cppconn/exception.h>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cassert>

namespace orm
{
    MySqlQuery::MySqlQuery(DB& db,const std::string& query) : Query(db,query), _dbRes(nullptr), _currentRes(nullptr), _numFieldsRes(0), _preparedStatement(nullptr)
    {
        //remove all ';' at the end
        auto s = query.size() -1;

        while(query[s] == ';')
        {
            --s;
        }

        if(s != query.size() - 1)
        {
            _query = query.substr(0,s + 1);
        }
    };

    MySqlQuery::~MySqlQuery()
    {
        if(_prepared and _preparedStatement)
        {
            mysql_stmt_close(_preparedStatement);
            _preparedStatement = nullptr;
        }

        if(_dbRes)
        {
            mysql_free_result(_dbRes);
        }


        for(MYSQL_BIND& param : _preparedParams)
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
                    std::cerr<<ORM_COLOUR_RED<<"??? MySqlQuery::~MySqlQuery() : Type "<<param.buffer_type<<" not bind"<<ORM_COLOUR_NONE<<std::endl;
                    assert(false && "This case should never apear");
                }break;

            }
        }

        //#error prepared_results

    };


    int MySqlQuery::_count()const
    {
        if(_prepared)
        {
            return mysql_stmt_num_rows(_preparedStatement);
        }

        return mysql_num_rows(_dbRes);

    };

    template<typename T>
    void _unpack_value(T& value,const char* buffer)
    {
        std::stringstream(buffer) >> value;
    }

    template<>
    void _unpack_value(std::string& value,const char* buffer)
    {
        value = buffer;
    }

    template<typename T>
    bool MySqlQuery::_getValue(T& value,const int& column)const
    {
        bool res = true;
        if(_prepared)
        {
            assert(column < int(_preparedResults.size()));

            if(*_preparedResults[column].is_null)
            {
                value = T();
                res = false;
            }
            else
            {
                int real_len = _preparedResultsBuffer[column].real_len;

                _preparedResultsBuffer[column].buffer[real_len + 1] = '\0';

                _unpack_value<T>(value,_preparedResultsBuffer[column].buffer.data());
            }

        }
        else
        {
            _unpack_value<T>(value,_currentRes[column]);
        }

        return res;
    }

    bool MySqlQuery::_get(bool& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(int& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_getPk(int& value, const int& column)const
    {
        bool res = _getValue(value,column);
        if(not res)
        {
            value = -1;
        }

        return res;
    }

    bool MySqlQuery::_get(unsigned int& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(long long int& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(long long unsigned int& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(float& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(double& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(long double& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(std::string& value,const int& column)const
    {
        return _getValue(value,column);
    };

    bool MySqlQuery::_get(struct tm& value,const int& column)const
    {
        bool res;

        std::string str;
        res = _get(str,column);
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

    bool MySqlQuery::_next()
    {
        int res = true;
        if(_prepared)
        {
            if(_numFieldsRes > 0)
            {
                res = mysql_stmt_fetch(_preparedStatement);
                if(res == 1)
                {
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::next() Error : "<<mysql_stmt_errno(_preparedStatement)<<" : "<<               mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                }
                else if (res == MYSQL_NO_DATA)
                {
                    //std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::next() MYSQL_NO_DATA : "<<mysql_stmt_error(prepared_statement)<<ORM_COLOUR_NONE<<std::endl;
                }
                else if (res == MYSQL_DATA_TRUNCATED)
                {
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::next() MYSQL_DATA_TRUNCATED : "<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                }

                res = not res;
            }

        }
        else
        {
            if(_dbRes)
            {
                _currentRes = mysql_fetch_row(_dbRes);
            }
            res =  (_currentRes != nullptr);
        }
        return res;
    }

    bool MySqlQuery::_set(const bool& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_TINY;
        _preparedParams[column].buffer = new bool(value);
        _preparedParams[column].buffer_length = sizeof(bool);

        return true;
    };

    bool MySqlQuery::_set(const int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_LONG;
        _preparedParams[column].buffer = new int(value);
        _preparedParams[column].buffer_length = sizeof(int);

        return true;
    };

    bool MySqlQuery::_set(const unsigned int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_LONG;
        _preparedParams[column].buffer = new unsigned int(value);
        _preparedParams[column].buffer_length = sizeof(unsigned int);
        _preparedParams[column].is_unsigned = true;

        return true;
    };

    bool MySqlQuery::_set(const long long int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_LONGLONG;
        _preparedParams[column].buffer = new long long int(value);
        _preparedParams[column].buffer_length = sizeof(long long int);
        return true;
    };

    bool MySqlQuery::_set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_LONGLONG;
        _preparedParams[column].buffer = new long long unsigned int(value);
        _preparedParams[column].buffer_length = sizeof(long long unsigned int);
        _preparedParams[column].is_unsigned = true;

        return true;
    };

    bool MySqlQuery::_set(const float& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_FLOAT;
        _preparedParams[column].buffer = new float(value);
        _preparedParams[column].buffer_length = sizeof(float);

        return true;
    };

    bool MySqlQuery::_set(const double& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_DOUBLE;
        _preparedParams[column].buffer = new double(value);
        _preparedParams[column].buffer_length = sizeof(double);

        return true;
    };

    bool MySqlQuery::_set(const long double& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_DOUBLE;
        _preparedParams[column].buffer = new double(value);
        _preparedParams[column].buffer_length = sizeof(double);

        return true;
    };

    bool MySqlQuery::_set(const std::string& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        const long unsigned int size = value.size();

        char* buffer = new char[size+1];
        memcpy(buffer,value.c_str(),size+1);

        _preparedParams[column].buffer_type = MYSQL_TYPE_STRING;
        _preparedParams[column].buffer = buffer;
        _preparedParams[column].buffer_length = size;
        _preparedParams[column].is_null_value = (size == 0);

        return true;
    };

    bool MySqlQuery::_set(const struct tm& value, const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        std::stringstream stream;
        stream<<std::setfill('0')
            <<std::setw(4)<<value.tm_year
            <<"-"<<std::setw(2)<<value.tm_mon
            <<"-"<<std::setw(2)<<value.tm_mday
            <<" "
            <<std::setw(2)<<value.tm_hour
            <<":"<<std::setw(2)<<value.tm_min
            <<":"<<std::setw(2)<<value.tm_sec;

        return _set(stream.str(),column);
    }

    bool MySqlQuery::_setNull(const int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }

        _resizePreparedParams(column);

        _preparedParams[column].buffer_type = MYSQL_TYPE_LONG;
        _preparedParams[column].buffer = new int(value);
        _preparedParams[column].buffer_length = sizeof(int);
        _preparedParams[column].is_null_value = true;

        return true;
    };

    void MySqlQuery::_executeQuery()
    {
        if(_prepared)
        {
            {
                MYSQL* con = dynamic_cast<MySqlDB*>(&_db)->_dbConn;
                _preparedStatement = mysql_stmt_init(con);
                if(_preparedStatement == nullptr)
                {
                    std::cerr<<"MySqlQuery::executeQuery() mysql_stmt_init(): Could not create the statement. Error message : "<< mysql_error(con) <<std::endl;
                    return;
                }
            }

            if(mysql_stmt_prepare(_preparedStatement,_query.c_str(),_query.size() + 1))
            {
                std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() mysql_stmt_prepare() : Could not execute the query. Error message:"<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                return;
            }

            for(unsigned int i=0;i<_preparedParams.size();++i)
            {
                _preparedParamsBuffer[i].real_len = _preparedParams[i].buffer_length;
                _preparedParamsBuffer[i].is_null = _preparedParams[i].is_null_value;

                _preparedParams[i].length = &_preparedParamsBuffer[i].real_len;
                _preparedParams[i].is_null = &(_preparedParamsBuffer[i].is_null);
            }


            if(mysql_stmt_bind_param(_preparedStatement,_preparedParams.data()))
            {
                std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() mysql_stmt_bind_param() "<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                return;
            }

            _dbRes = mysql_stmt_result_metadata(_preparedStatement);

            if(_dbRes == nullptr)
            {
                _numFieldsRes = 0;
                //std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() mysql_stmt_result_metadata() : db_res == nullptr. Error: "<<mysql_stmt_error(prepared_statement)<<ORM_COLOUR_NONE<<std::endl;
                //return;
            }
            else
            {//for results length
                my_bool arg = 1;
                if(mysql_stmt_attr_set(_preparedStatement,STMT_ATTR_UPDATE_MAX_LENGTH,&arg))
                {
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() mysql_stmt_attr_set Error:"<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                    return;
                }
            }


            if(mysql_stmt_execute(_preparedStatement))
            {
                std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() : mysql_stmt_execute(), failed. Error messuge: "<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                return;
            }

            if(_dbRes)
            {

                if (mysql_stmt_store_result(_preparedStatement))
                {
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() : mysql_stmt_store_result(), failed. Error messuge: "<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                    return;
                }

                _numFieldsRes = mysql_num_fields(_dbRes);

                if(!_initResults())
                {
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() _initResults() : Could not execute prepare the results"<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                    return;
                }

                if(mysql_stmt_bind_result(_preparedStatement,_preparedResults.data()))
                {
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() mysql_stmt_bind_result() : "<<mysql_stmt_error(_preparedStatement)<<ORM_COLOUR_NONE<<std::endl;
                    return;
                }
            }

        }
        else
        {
            MYSQL* con = dynamic_cast<MySqlDB*>(&_db)->_dbConn;

            if(mysql_query(con,_query.c_str()))
            {
                std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() : Could not execute the query. Error message:"<<mysql_error(con)<<ORM_COLOUR_NONE<<std::endl;
                return;
            }

            _dbRes = mysql_store_result(con);
            if(_dbRes == nullptr)
            {
                if(mysql_errno(con)) // mysql_store_result() returned nothing; should it have?
                {
                    // query should return data
                    // (it was a SELECT)
                    std::cerr<<ORM_COLOUR_RED<<"MySqlQuery::executeQuery() : Could not get query results. Error message:"<<mysql_error(con)<<ORM_COLOUR_NONE<<std::endl;
                }
                return;
            }
            //num_fields_res = mysql_num_fields(db_res);

        }

    }

    bool MySqlQuery::_initResults()
    {

        _preparedResults.clear();
        _preparedResults.resize(_numFieldsRes);
        std::memset(_preparedResults.data(), 0, sizeof(MYSQL_BIND)*_numFieldsRes);

        _preparedResultsBuffer.clear();
        _preparedResultsBuffer.resize(_numFieldsRes);


        for(int i = 0;i< _numFieldsRes;++i)
        {
            MYSQL_FIELD* field = &(_dbRes->fields[i]);
            int len = field->max_length;
            len = len>0?len:1;

            _preparedResultsBuffer[i].buffer.resize(len + 1,'\0');

            _preparedResults[i].buffer_type = MYSQL_TYPE_STRING;
            _preparedResults[i].buffer = &(_preparedResultsBuffer[i].buffer[0]);
            _preparedResults[i].buffer_length = len;

            _preparedResults[i].is_null = &_preparedResultsBuffer[i].is_null;
            _preparedResults[i].length = &(_preparedResultsBuffer[i].real_len);
        }

        return true;
    }

    void MySqlQuery::_resizePreparedParams(unsigned int s)
    {
        unsigned int size = _preparedParams.size();
        if(size < ++s)
        {
            MYSQL_BIND n;
            memset(&n,0,sizeof(MYSQL_BIND));
            _preparedParams.resize(s,n);
            ResultData data;
            data.is_null = false;
            data.real_len = 0;
            _preparedParamsBuffer.resize(s,data);
        }

    }

};
