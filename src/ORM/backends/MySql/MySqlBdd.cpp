#include  <ORM/backends/MySql/MySqlBdd.hpp>
#include  <ORM/backends/MySql/MySqlQuery.hpp>

#include <ORM/fields/private/VAttr.hpp>
#include <ORM/backends/op.hpp>

#include <cppconn/exception.h>

namespace orm
{
    MySqlTableCreator MySqlBdd::my_creator;

    MySqlBdd::MySqlBdd(std::string username,std::string pass,std::string bdd,std::string serveur,std::string port) :
        Bdd(username,pass,bdd,serveur,port),
        driver(0),
        dbConn(0)
    {
        //Operators
        operators[op::exact]= " = %s";
        operators[op::iexact]= " LIKE %s";
        operators[op::contains]= " LIKE BINARY %s";
        operators[op::icontains]= " LIKE %s";
        operators[op::regex]= " REGEXP BINARY %s";
        operators[op::iregex]= " REGEXP %s";
        operators[op::gt]= " > %s";
        operators[op::gte]= " >= %s";
        operators[op::lt]= " < %s";
        operators[op::lte]= " <= %s";
        operators[op::startswith]= " LIKE BINARY %s";
        operators[op::endswith]= " LIKE BINARY %s";
        operators[op::istartswith]= " LIKE %s";
        operators[op::iendswith]= " LIKE %s";

        //ordering
        operators["?"] = " RAND() ";
        operators["+"] = " ASC ";
        operators["-"] = " DESC ";

        //escape_char = "";
    };

    MySqlBdd::~MySqlBdd()
    {
        if(dbConn)
            delete dbConn;
    };

    Bdd* MySqlBdd::clone()const
    {
        MySqlBdd* copy = new MySqlBdd(this->s_username,this->s_password,this->s_bdd_name,this->s_serveur,this->s_port);
        return copy;
    }
    
    bool MySqlBdd::connect()
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
        statement->execute("USE "+escapeColumn(s_bdd_name));

        std::cerr<<"MySqlBdd::Connect to "<<s_serveur<<" using database: "<<s_bdd_name<<std::endl;

        delete statement;

        return true;
    };

    bool MySqlBdd::disconnect()
    {
        return true;
    };

    void MySqlBdd::threadInit()
    {
        driver->threadInit();
    }

    void MySqlBdd::threadEnd()
    {
        driver->threadEnd();
    }

    Query* MySqlBdd::query(const std::string& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };

    Query* MySqlBdd::query(std::string&& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };


    Query* MySqlBdd::prepareQuery(const std::string& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    };

    Query* MySqlBdd::prepareQuery(std::string&& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    }

    bool MySqlBdd::create(const std::string& table,const std::vector<const VAttr*>& attrs)
    {
        std::string sql = "CREATE TABLE \""+table+"\"(\n";
        unsigned int size = attrs.size();
        sql+= creator().autoField("id");

        const Bdd& bdd=*this;
        sql+=attrs[0]->create(bdd);
        for(unsigned int i=0;i<size;++i)
        {
            sql+=",\n"+attrs[i]->create(bdd);
        }
        sql+="\n);";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    bool MySqlBdd::drop(const std::string& table)
    {
        std::string sql = "DROP TABLE \""+table+"\";";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    bool MySqlBdd::clear(const std::string& table)
    {

        std::string sql = "TRUNCATE \""+table+"\";";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    /************** PROTECTED **********************/
    
    void MySqlBdd::beginTransaction()
    {
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("START TRANSACTION;");
        delete statement;
    };

    void MySqlBdd::endTransaction()
    {
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("COMMIT;");
        delete statement;
    };

    void MySqlBdd::rollback()
    {
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("ROLLBACK;");
        delete statement;
    };

    int MySqlBdd::getLastInsertPk()
    {
        Query& q = *query("SELECT LAST_INSERT_ID();");

        q.execute();
        q.next();

        int pk = -1;
        q.get(pk,getInitialGetcolumnNumber());

        delete &q;

        return pk;
    }

    std::string MySqlBdd::escapeColumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int MySqlBdd::getInitialGetcolumnNumber() const
    {
        return 1;
    }

    std::string MySqlBdd::limit(const int& skip,const int& count)const
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
    
    const TableCreator& MySqlBdd::creator() const
    {
        return my_creator;
    }
    
};
