#include  <ORM/backends/Sqlite3/Sqlite3Bdd.hpp>
#include  <ORM/backends/Sqlite3/Sqlite3Query.hpp>


namespace orm
{
    Sqlite3Bdd::Sqlite3Bdd(std::string bdd) : Bdd("","",bdd,"",""), dbConn(0)

    {
        //operators
        operators["exact"]= " = %s";
        operators["iexact"]= " LIKE %s ESCAPE '\\'";
        operators["contains"]= " LIKE %s ESCAPE '\\'";
        operators["icontains"]= " LIKE %s ESCAPE '\\'";
        operators["regex"]= " REGEXP %s";
        operators["iregex"]= " REGEXP '(?i)' || %s";
        operators["gt"]= " > %s";
        operators["gte"]= " >= %s";
        operators["lt"]= " < %s";
        operators["lte"]= " <= %s";
        operators["startswith"]= " LIKE %s ESCAPE '\\'";
        operators["endswith"]= " LIKE %s ESCAPE '\\'";
        operators["istartswith"]= " LIKE %s ESCAPE '\\'";
        operators["iendswith"]= " LIKE %s ESCAPE '\\'";
        
        //ordering
        operators["?"] = "RAND() ";
        operators["+"] = "ASC ";
        operators["-"] = "DESC ";

    };

    Sqlite3Bdd::~Sqlite3Bdd()
    {
        /*
        if(statement)
            delete statement;
        */
        if(dbConn)
            sqlite3_close(dbConn);
    };
    
    bool Sqlite3Bdd::connect()
    {

        /* open the database */
        int result=sqlite3_open(s_bdd_name.c_str(),&dbConn);
        if (result != SQLITE_OK)
        {
            std::cerr<<"Failed to open database "/*<<sqlite3_errstr(result)*/<<std::endl;
            sqlite3_close(dbConn);
            return false;
        }

        return true;
    };

    bool Sqlite3Bdd::disconnect()
    {
        int result = sqlite3_close(dbConn);
        if (result != SQLITE_OK)
        {
            std::cerr<<"Failed to close database "/*<<sqlite3_errstr(result)*/<<std::endl;
            return false;
        }
        return true;
    };

    Query* Sqlite3Bdd::query(const std::string& str)
    {
        return new Sqlite3Query(this,str);
    };

    Query* Sqlite3Bdd::query(std::string&& str)
    {
        return new Sqlite3Query(this,str);
    };


    Query* Sqlite3Bdd::prepareQuery(const std::string& str)
    {
        auto q = new Sqlite3Query(this,str);
        /// \todo q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    };

    Query* Sqlite3Bdd::prepareQuery(std::string&& str)
    {
        auto q = new Sqlite3Query(this,str);
        /// \todo q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    }

    /************** PROTECTED **********************/


    int Sqlite3Bdd::getLastInsertPk()
    {
        return (int)sqlite3_last_insert_rowid(dbConn);
    }

    std::string Sqlite3Bdd::escapeColum(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int Sqlite3Bdd::getInitialGetColumnNumber() const
    {
        return 0;
    }

    std::string Sqlite3Bdd::escapeValue(const std::string& filter,const std::string& value) const
    {

        std::string formated_value;

        /*if(filter == "contains")
        {
            formated_value = Bdd::escapeValue("%"+value+"%");
        }
        else if(filter == "icontains")
        {
            formated_value = Bdd::escapeValue("%"+value+"%");
        }
        else if(filter == "startswith")
        {
            formated_value = Bdd::escapeValue(value+"%");
        }
        else if(filter == "endswith" )
        {
            formated_value = Bdd::escapeValue("%"+value);
        }
        else if(filter == "istartswith")
        {
            formated_value = Bdd::escapeValue(value+"%");
        }
        else if(filter == "iendswith")
        {
            formated_value = Bdd::escapeValue("%"+value);
        }
        else
        {
            formated_value =  Bdd::escapeValue(value);
        }*/
        formated_value =  Bdd::escapeValue(value);

        const std::string& op = operators.at(filter);
        char buffer[formated_value.size() + op.size()];
        sprintf(buffer,op.c_str(),formated_value.c_str());

        return std::string(buffer);
    }

    std::string Sqlite3Bdd::limit(const int& skip,const int& count) const
    {
        std::string query;
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(count)+" OFFEST "+std::to_string(skip);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        else
            std::cerr<<ROUGE<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        return query;
    };



};
