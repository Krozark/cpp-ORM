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
        operators["?"] = "RANDOM() ";
        operators["+"] = "ASC ";
        operators["-"] = "DESC ";

    };

    Sqlite3Bdd::~Sqlite3Bdd()
    {
        if(dbConn)
            sqlite3_close(dbConn);
    };
    
    bool Sqlite3Bdd::connect()
    {
        /* open the database */
        int result=sqlite3_open(s_bdd_name.c_str(),&dbConn);
        if (result != SQLITE_OK)
        {
            ORM_PRINT_ERROR("Sqlite3Bdd::connect() Failed to open database ")
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
            ORM_PRINT_WARNING("Sqlite3Bdd::disconnect() Failed to close database")
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
        Sqlite3Query* q = new Sqlite3Query(this,str);
        q->prepared = true;
        return q;
    };

    Query* Sqlite3Bdd::prepareQuery(std::string&& str)
    {
        Sqlite3Query* q = new Sqlite3Query(this,str);
        q->prepared = true;
        return q;
    }

    /************** PROTECTED **********************/


    int Sqlite3Bdd::getLastInsertPk()
    {
        return (int)sqlite3_last_insert_rowid(dbConn);
    }

    std::string Sqlite3Bdd::escapecolumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int Sqlite3Bdd::getInitialGetcolumnNumber() const
    {
        return 0;
    }


    std::string Sqlite3Bdd::limit(const int& skip,const int& count) const
    {
        std::string query;
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(count)+" OFFEST "+std::to_string(skip);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        #if ORM_VERBOSITY & ORM_WARNING
        else
            ORM_PRINT_WARNING("Sqlite3Bdd::Limit(skip,count) count can't be <= 0")
        #endif
        return query;
    };
};
