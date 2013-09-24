#include  <ORM/backends/MySql/MySQLBdd.hpp>
#include  <ORM/backends/MySql/MySQLQuery.hpp>

#include <cppconn/exception.h>

namespace orm
{
    MySQLBdd::MySQLBdd(std::string username,std::string pass,std::string bdd,std::string serveur,std::string port) :
        Bdd(username,pass,bdd,serveur,port),
        driver(0),
        dbConn(0)
    {
        //Operators
        operators["exact"] = " = ";
        operators["iexact"] = " LIKE ";
        operators["contains"]= " LIKE BINARY ";
        operators["icontains"]= " LIKE ";
        operators["regex"]= " REGEXP BINARY ";
        operators["iregex"]= " REGEXP ";
        operators["gt"]= " > ";
        operators["gte"]= " >= ";
        operators["lt"]= " < ";
        operators["lte"]= " <= ";
        operators["startswith"]= " LIKE BINARY ";
        operators["endswith"]= " LIKE BINARY ";
        operators["istartswith"]= " LIKE ";
        operators["iendswith"]= " LIKE ";

        //ordering
        operators["?"] = " RAND() ";
        operators["+"] = " ASC ";
        operators["-"] = " DESC ";

        //escape_char = "";
    };

    MySQLBdd::~MySQLBdd()
    {
        /*if(statement)
            delete statement;
        */
        if(dbConn)
            delete dbConn;
    };
    
    bool MySQLBdd::connect()
    {
        try{
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
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("USE "+s_bdd_name);

        std::cerr<<"MySQLBdd::Connect to "<<s_serveur<<" using database: "<<s_bdd_name<<std::endl;

        delete statement;

        return true;
    };

    bool MySQLBdd::disconnect()
    {
        return true;
    };

    Query* MySQLBdd::query()
    {
        auto q = new MySQLQuery(this);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };

    Query* MySQLBdd::query(const std::string& str)
    {
        auto q = new MySQLQuery(this,str);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };

    Query* MySQLBdd::query(std::string&& str)
    {
        auto q = new MySQLQuery(this,str);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };


    Query* MySQLBdd::prepareQuery(const std::string& str)
    {
        auto q = new MySQLQuery(this,str);
        q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    };

    Query* MySQLBdd::prepareQuery(std::string&& str)
    {
        auto q = new MySQLQuery(this,str);
        q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    }

    /************** PROTECTED **********************/

    /*bool MySQLBdd::executeQuery(Query& query)
    {
        MySQLQuery& q = dynamic_cast<MySQLQuery&>(query);
        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<"\033[32m"<<query.query<<"\033[00m"<<std::endl;
        #endif
        if(query.prepared)
        {
            q.bdd_res = 0;
            return q.prepared_statement->execute();
        }
        else
        {
            q.bdd_res = statement->executeQuery(q.query);
            return true;
        }
    };*/

    int MySQLBdd::getLastInsertPk()
    {
        Query& q = *query("SELECT LAST_INSERT_ID()");

        q.execute();
        q.next();

        int pk = -1;
        q.get(pk,0);

        delete &q;

        return pk;
    }

    std::string MySQLBdd::escapeColum(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int MySQLBdd::getInitialGetColumnNumber() const
    {
        return 1;
    }

};
