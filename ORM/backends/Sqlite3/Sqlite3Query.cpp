#include <ORM/backends/Sqlite3/Sqlite3Query.hpp>
#include <ORM/backends/Sqlite3/Sqlite3Bdd.hpp>


namespace orm
{
    Sqlite3Query::Sqlite3Query(Bdd* bdd,const std::string& query) : Query(bdd,query), statement(0)
    {
        int result = sqlite3_prepare_v2(static_cast<Sqlite3Bdd*>(bdd)->dbConn,query.c_str(),query.size()+1, &statement, NULL);
        if (result != SQLITE_OK)
        {
            std::cerr<<ROUGE<<"[Query] Failed to make the statment"<<BLANC<<std::endl;
            /// \todo <<sqlite3_errstr(result)<<std::endl;
        }
    };

    Sqlite3Query::Sqlite3Query(Bdd* bdd,std::string&& query) : Query(bdd,query), statement(0)
    {
        int result = sqlite3_prepare_v2(static_cast<Sqlite3Bdd*>(bdd)->dbConn,query.c_str(),query.size()+1, &statement, NULL);
        if (result != SQLITE_OK)
        {
            std::cerr<<ROUGE<<"[Query] Failed to make the statment"<<BLANC<<std::endl;
            /// \todo <<sqlite3_errstr(result)<<std::endl;
        }
    };

    Sqlite3Query::~Sqlite3Query()
    {
        if(statement)
        {
            int result = sqlite3_finalize(statement);
            if(result != SQLITE_OK)
            {
                std::cerr<<ROUGE<<"[Query] Failed to close the statement"<<BLANC<<std::endl;
                /// \todo <<sqlite3_errstr(result)<<std::endl;
            }
        }
    };

    Sqlite3Query& Sqlite3Query::limit(const int& skip,const int& count)
    {
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(count)+" OFFEST "+std::to_string(skip);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        else
            std::cerr<<ROUGE<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        return *this;
    };

    int Sqlite3Query::count()const
    {
        return sqlite3_data_count(statement);
    };

    bool Sqlite3Query::get(bool& value,const int& colum)const
    {
        value = (bool)sqlite3_column_int(statement,colum);
        return true;
    };

    bool Sqlite3Query::get(int& value,const int& colum)const
    {
        value = sqlite3_column_int(statement,colum);
        return true;
    };

    bool Sqlite3Query::get(unsigned int& value,const int& colum)const
    {
        value = (unsigned int)sqlite3_column_int(statement,colum);
        return true;
    };

    bool Sqlite3Query::get(long long int& value,const int& colum)const
    {    
        value = (long long int)sqlite3_column_int64(statement,colum);
        return true;
    };

    bool Sqlite3Query::get(long long unsigned int& value,const int& colum)const
    {
        value = (unsigned long long int)sqlite3_column_int64(statement,colum);

        return true;
    };

    bool Sqlite3Query::get(float& value,const int& colum)const
    {
        value = (float)sqlite3_column_double(statement,colum);
        return true;
    };

    bool Sqlite3Query::get(long double& value,const int& colum)const
    {
        value = (long double)sqlite3_column_double(statement,colum);
        return true;
    };

    bool Sqlite3Query::get(std::string& value,const int& colum)const
    {
        const unsigned char* res = sqlite3_column_text(statement,colum);

        if (res)
            value = (const char*)res;
        else
            value = "";

        return true;
    };

    bool Sqlite3Query::next()
    {
        return(sqlite3_step(statement) == SQLITE_ROW);
    }

    bool Sqlite3Query::set(const bool& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int(statement,(int)colum,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int(statement,(int)colum,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const unsigned int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int(statement,(int)colum,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const long long int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int64(statement,(int)colum,(sqlite3_int64)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const long long unsigned int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int64(statement,(int)colum,(sqlite3_int64)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const float& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_double(statement,(int)colum,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const long double& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_double(statement,(int)colum,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const std::string& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_text(statement,(int)colum,value.c_str(),value.size(),SQLITE_STATIC)== SQLITE_OK);
    };

    bool Sqlite3Query::setNull(const int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_null(statement,(int)colum)== SQLITE_OK);
    };

    bool Sqlite3Query::executeQuery()
    {
        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<"\033[32m"<<query<<"\033[00m"<<std::endl;
        #endif

        if(prepared)
            return next();
        return true;
    };
    
};
