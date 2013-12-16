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
        operators["exact"]= " = %s";
        operators["iexact"]= " LIKE %s";
        operators["contains"]= " LIKE BINARY %s";
        operators["icontains"]= " LIKE %s";
        operators["regex"]= " REGEXP BINARY %s";
        operators["iregex"]= " REGEXP %s";
        operators["gt"]= " > %s";
        operators["gte"]= " >= %s";
        operators["lt"]= " < %s";
        operators["lte"]= " <= %s";
        operators["startswith"]= " LIKE BINARY %s";
        operators["endswith"]= " LIKE BINARY %s";
        operators["istartswith"]= " LIKE %s";
        operators["iendswith"]= " LIKE %s";

        //ordering
        operators["?"] = " RAND() ";
        operators["+"] = " ASC ";
        operators["-"] = " DESC ";

        //escape_char = "";
    };

    MySQLBdd::~MySQLBdd()
    {
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

    std::string MySQLBdd::escapeColumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int MySQLBdd::getInitialGetcolumnNumber() const
    {
        return 1;
    }

    std::string MySQLBdd::limit(const int& skip,const int& count)const
    {
        std::string query;
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(skip)+" , "+std::to_string(count);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        else
            std::cerr<<ROUGE<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        return query;
    };
    
};
