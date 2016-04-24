#include <ORM/backends/Sqlite3/Sqlite3Query.hpp>
#include <ORM/backends/Sqlite3/Sqlite3DB.hpp>

#include <sstream>
#include <iomanip>


namespace orm
{
    Sqlite3Query::Sqlite3Query(DB& db,const std::string& query) :
        Query(db,query),
        _statement(0)
    {
        int result = sqlite3_prepare_v2(static_cast<Sqlite3DB&>(db)._dbConn,query.c_str(),query.size()+1, &_statement, NULL);

        #if ORM_VERBOSITY & ORM_ERROR
        if (result != SQLITE_OK)
        {
            ORM_PRINT_ERROR("Sqlite3Query::Sqlite3Query(db,string&) Failed to make the statment : "
            <<sqlite3_errstr(result));
        }
        #endif
    };

    Sqlite3Query::Sqlite3Query(DB& _db,std::string&& _query) :
        Query(_db,_query),
        _statement(0)
    {
        int result = sqlite3_prepare_v2(static_cast<Sqlite3DB&>(_db)._dbConn,_query.c_str(),_query.size()+1, &_statement, NULL);

        #if ORM_VERBOSITY & ORM_ERROR
        if (result != SQLITE_OK)
        {
            ORM_PRINT_ERROR("Sqlite3Query::Sqlite3Query(db,string&&) Failed to make the statment")
            /// \todo <<sqlite3_errstr(result)<<std::endl;
        }
        #endif
    };

    Sqlite3Query::~Sqlite3Query()
    {
        if(_statement)
        {
            int result = sqlite3_finalize(_statement);

            #if ORM_VERBOSITY & ORM_ERROR
            if(result != SQLITE_OK)
            {
                ORM_PRINT_ERROR("Sqlite3Query::~Sqlite3Query() Failed to close the statement")
                /// \todo <<sqlite3_errstr(result)<<std::endl;
            }
            #endif
        }
    };


    int Sqlite3Query::_count()const
    {
        return sqlite3_data_count(_statement);
    };

    bool Sqlite3Query::_get(bool& value,const int& column)const
    {
        value = (bool)sqlite3_column_int(_statement,column);
        return true;
    };

    bool Sqlite3Query::_get(int& value,const int& column)const
    {
        value = sqlite3_column_int(_statement,column);
        return true;
    };

    bool Sqlite3Query::_getPk(int& value, const int& column)const
    {
        if(sqlite3_column_type(_statement,column) == SQLITE_NULL)
        {
            value = -1;
            return false;
        }
        value = sqlite3_column_int(_statement,column);
        return true;
    }

    bool Sqlite3Query::_get(unsigned int& value,const int& column)const
    {
        value = (unsigned int)sqlite3_column_int(_statement,column);
        return true;
    };

    bool Sqlite3Query::_get(long long int& value,const int& column)const
    {
        value = (long long int)sqlite3_column_int64(_statement,column);
        return true;
    };

    bool Sqlite3Query::_get(long long unsigned int& value,const int& column)const
    {
        value = (unsigned long long int)sqlite3_column_int64(_statement,column);

        return true;
    };

    bool Sqlite3Query::_get(float& value,const int& column)const
    {
        value = (float)sqlite3_column_double(_statement,column);
        return true;
    };

    bool Sqlite3Query::_get(double& value,const int& column)const
    {
        value = (double)sqlite3_column_double(_statement,column);
        return true;
    };

    bool Sqlite3Query::_get(long double& value,const int& column)const
    {
        value = (long double)sqlite3_column_double(_statement,column);
        return true;
    };

    bool Sqlite3Query::_get(std::string& value,const int& column)const
    {
        const unsigned char* res = sqlite3_column_text(_statement,column);

        if (res)
        {
            value = (const char*)res;
        }
        else
        {
            value = "";
        }

        return true;
    };

    bool Sqlite3Query::_get(tm& value,const int& column)const
    {
        bool res = false;
        const unsigned char* str = sqlite3_column_text(_statement,column);
        if (str)
        {
            int year,mon,day,hour,min,sec;
            res = ::sscanf((const char*)str,"%4d-%2d-%2d %2d:%2d:%2d",&year,&mon,&day,&hour,&min,&sec) == 6;
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

    bool Sqlite3Query::_next()
    {
        int result = sqlite3_step(_statement);
        if(result == SQLITE_ROW)
        {
            return true;
        }
        else if(result == SQLITE_DONE)
        {
            return false;
        }

        ORM_PRINT_ERROR("Sqlite3Query::next() imposible to get next row, error:"<<result)
        ///\todo sqlite3_errstr(result)<<std::endl;

        return false;

    }

    bool Sqlite3Query::_set(const bool& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_int(_statement,(int)column,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_int(_statement,(int)column,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const unsigned int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_int(_statement,(int)column,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const long long int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_int64(_statement,(int)column,(sqlite3_int64)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_int64(_statement,(int)column,(sqlite3_int64)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const float& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_double(_statement,(int)column,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const double& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_double(_statement,(int)column,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const long double& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_double(_statement,(int)column,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const std::string& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_text(_statement,(int)column,value.c_str(),-1,SQLITE_TRANSIENT)== SQLITE_OK);
    };

    bool Sqlite3Query::_set(const tm& value, const unsigned int& column)
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
        return (sqlite3_bind_text(_statement,(int)column,stream.str().c_str(),-1,SQLITE_TRANSIENT)== SQLITE_OK);

    }

    bool Sqlite3Query::_setNull(const int& value,const unsigned int& column)
    {
        if(not _prepared)
        {
            return false;
        }
        return (sqlite3_bind_null(_statement,(int)column)== SQLITE_OK);
    };


    void Sqlite3Query::_executeQuery()
    {
    };

};
