#include <ORM/backends/Sqlite3/Sqlite3Query.hpp>


namespace orm
{
    Sqlite3Query::Sqlite3Query(Bdd* bdd) : Query(bdd)/*, bdd_res(0), prepared_statement(0)*/
    {
    };

    Sqlite3Query::Sqlite3Query(Bdd* bdd,const std::string& query) : Query(bdd,query)/*, bdd_res(0), prepared_statement(0)*/
    {
    };

    Sqlite3Query::Sqlite3Query(Bdd* bdd,std::string&& query) : Query(bdd,query)/*, bdd_res(0), prepared_statement(0)*/
    {
    };

    Sqlite3Query::~Sqlite3Query()
    {
        /** \todo
        if(prepared and prepared_statement)
            delete prepared_statement;
        if(bdd_res)
            delete bdd_res;
        */
    };

    Sqlite3Query& Sqlite3Query::limit(const int& skip,const int& count)
    {
        /**
         \todo
         if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(skip)+" , "+std::to_string(count);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        else
            std::cerr<<ROUGE<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        */
        return *this;
    };

    int Sqlite3Query::count()const
    {
        /** \todo return bdd_res->rowsCount();*/
    };

    bool Sqlite3Query::get(bool& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getBoolean(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(int& value,const std::string& colum)const
    {

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(unsigned int& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(long long int& value,const std::string& colum)const
    {    
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getInt64(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(long long unsigned int& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getUInt64(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(float& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = static_cast<float>(bdd_res->getDouble(colum));
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(long double& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getDouble(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    bool Sqlite3Query::get(std::string& value,const std::string& colum)const
    {
        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr : "<<colum<<BLANC<<std::endl;
        #endif

        /*#if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = bdd_res->getString(colum);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif*/
        return true;
    };

    //std::istream * getBlob

    bool Sqlite3Query::next()
    {
        //return bdd_res->next();
    }

    bool Sqlite3Query::set(const bool& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setBoolean(colum,value);
        return true;
    };

    bool Sqlite3Query::set(const int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setInt(colum,value);
        return true;
    };

    bool Sqlite3Query::set(const unsigned int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setUInt(colum,value);
        return true;
    };

    bool Sqlite3Query::set(const long long int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setInt64(colum,value);
        return true;
    };

    bool Sqlite3Query::set(const long long unsigned int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setUInt64(colum,value);
        return true;
    };

    bool Sqlite3Query::set(const float& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setDouble(colum,static_cast<double>(value));
        return true;
    };

    bool Sqlite3Query::set(const long double& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setDouble(colum,value);
        return true;
    };

    bool Sqlite3Query::set(const std::string& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setString(colum,value);
        return true;
    };

    bool Sqlite3Query::setNull(const int& value,const unsigned int& colum)
    {
        if(not prepared)
            return false;
        //prepared_statement->setNull(colum,sql::DataType::INTEGER);
        return true;
    };
};
