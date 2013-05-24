#include "MySQLBdd.hpp"
#include "MySQLQuery.hpp"

#include <cppconn/exception.h>

namespace orm
{
    MySQLBdd::MySQLBdd(std::string username,std::string pass,std::string bdd,std::string serveur,std::string port) :
        Bdd(username,pass,bdd,serveur,port),
        driver(0),
        dbConn(0)
    {
        operators["exact"] = "= ";
        operators["iexact"] = "LIKE ";
        operators["contains"]= "LIKE BINARY ";
        operators["icontains"]= "LIKE ";
        operators["regex"]= "REGEXP BINARY ";
        operators["iregex"]= "REGEXP ";
        operators["gt"]= "> ";
        operators["gte"]= ">= ";
        operators["lt"]= "< ";
        operators["lte"]= "<= ";
        operators["startswith"]= "LIKE BINARY ";
        operators["endswith"]= "LIKE BINARY ";
        operators["istartswith"]= "LIKE ";
        operators["iendswith"]= "LIKE ";
    };

    MySQLBdd::~MySQLBdd()
    {
        if(statement)
            delete statement;
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
        statement = dbConn->createStatement();
        statement->execute("USE "+s_bdd_name);

        std::cerr<<"MySQLBdd::Connect to "<<s_serveur<<" using table: "<<s_bdd_name<<std::endl;

        return true;
    };

    bool MySQLBdd::disconnect()
    {
        return true;
    };

    Query* MySQLBdd::query()
    {
        return new MySQLQuery(this);
    };

    Query* MySQLBdd::query(const std::string& str)
    {
        return new MySQLQuery(this,str);
    };

    Query* MySQLBdd::query(std::string&& str)
    {
        return new MySQLQuery(this,str);
    };

    /* manualy create  a query */
    Query* MySQLBdd::prepareQuery()
    {
        auto q = new MySQLQuery(this);
        q->prepared = true;
        return q;
    };

    Query* MySQLBdd::prepareQuery(const std::string& str)
    {
        auto q = new MySQLQuery(this,str);
        q->prepared = true;
        return q;
    };

    Query* MySQLBdd::prepareQuery(std::string&& str)
    {
        auto q = new MySQLQuery(this,str);
        q->prepared = true;
        return q;
    }

    /************** PROTECTED **********************/

    bool MySQLBdd::executeQuery(Query& query)
    {
        MySQLQuery& q = dynamic_cast<MySQLQuery&>(query);
        if(query.prepared)
        {
            q.bdd_res = q.prepared_statement->executeQuery();
        }
        else
        {
            q.bdd_res = statement->executeQuery(q.query);
        }
    };
    
};
