#include  <ORM/backends/Sqlite3/Sqlite3Bdd.hpp>
#include  <ORM/backends/Sqlite3/Sqlite3Query.hpp>


namespace orm
{
    Sqlite3Bdd::Sqlite3Bdd(std::string bdd) : Bdd("","",bdd,"","")/*,driver(0)*/, dbConn(0)

    {
        //Operators
        operators["exact"] = "= ";
        //operators["iexact"] = "LIKE ";
        //operators["contains"]= "LIKE BINARY ";
        //operators["icontains"]= "LIKE ";
        //operators["regex"]= "REGEXP BINARY ";
        //operators["iregex"]= "REGEXP ";
        operators["gt"]= "> ";
        operators["gte"]= ">= ";
        operators["lt"]= "< ";
        operators["lte"]= "<= ";
        //operators["startswith"]= "LIKE BINARY ";
        //operators["endswith"]= "LIKE BINARY ";
        //operators["istartswith"]= "LIKE ";
        //operators["iendswith"]= "LIKE ";

        //ordering
        operators["?"] = "RAND() ";
        operators["+"] = "ASC ";
        operators["-"] = "DESC ";

        //escape_char = "";
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

};
