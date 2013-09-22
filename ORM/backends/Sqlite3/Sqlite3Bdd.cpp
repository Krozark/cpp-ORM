#include  <ORM/backends/Sqlite3/Sqlite3Bdd.hpp>
#include  <ORM/backends/Sqlite3/Sqlite3Query.hpp>


namespace orm
{
    Sqlite3Bdd::Sqlite3Bdd(std::string bdd) : Bdd("","",bdd,"","")
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
        /**if(statement)
            delete statement;
        if(dbConn)
            delete dbConn;*/
    };
    
    bool Sqlite3Bdd::connect()
    {
        /*try{
            driver = get_driver_instance();
        }catch (sql::SQLException e){
            std::cerr << "Could not get a database driver. Error message: " << e.what() <<std::endl;
            return false;
        }

        try{
            dbConn = driver->connect(s_serveur+":"+s_port,s_username,s_password);
        }
        catch (sql::SQLException e){
            std::cerr<< "Could not connect to database. Error message: " << e.what() << std::endl;
            return false;
        }
        statement = dbConn->createStatement();
        statement->execute("USE "+s_bdd_name);

        std::cerr<<"Sqlite3Bdd::Connect to "<<s_serveur<<" using database: "<<s_bdd_name<<std::endl;*/

        return true;
    };

    bool Sqlite3Bdd::disconnect()
    {
        return true;
    };

    Query* Sqlite3Bdd::query()
    {
        return new Sqlite3Query(this);
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

    bool Sqlite3Bdd::executeQuery(Query& query)
    {
        Sqlite3Query& q = dynamic_cast<Sqlite3Query&>(query);
        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<"\033[32m"<<query.query<<"\033[00m"<<std::endl;
        #endif

        if(query.prepared)
        {
            //q.bdd_res = 0;
            /// \todo return q.prepared_statement->execute();
        }
        else
        {
            /// \todo q.bdd_res = statement->executeQuery(q.query);
            return true;
        }
    };

    int Sqlite3Bdd::getLastInsertPk()
    {
        /**
         * \todo
        Query& q = *query("SELECT LAST_INSERT_ID()");

        executeQuery(q);
        q.next();

        int pk = -1;
        q.get(pk,"LAST_INSERT_ID()");

        delete &q;*/

        return -1;
    }

    std::string Sqlite3Bdd::escapeColum(const std::string& str) const
    {
        return "`"+str+"`";
    }
};
