#include  <ORM/backends/MySql/MySqlDB.hpp>
#include  <ORM/backends/MySql/MySqlQuery.hpp>

#include <ORM/fields/private/VAttr.hpp>
#include <ORM/backends/op.hpp>

//#include <my_global.h>

#include <mutex>

std::mutex _counterMutex;
int _counter = 0;

namespace orm
{
    MySqlTableCreator MySqlDB::my_creator;

    MySqlDB::MySqlDB(const std::string& username,const std::string& pass,const std::string& db,const std::string& serveur,int port) :
        DB(username,pass,db,serveur,port),
        dbConn(nullptr)
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

        {
            std::lock_guard<std::mutex> guard(_counterMutex);
            if (_counter++ == 0)
            {
                if(mysql_library_init(0,nullptr,nullptr))
                {
                    std::cerr<<"Unable to initialize MySQL library"<<std::endl;
                }
            }
        }

        //escape_char = "";
    };

    MySqlDB::~MySqlDB()
    {
        disconnect();

        {
            std::lock_guard<std::mutex> guard(_counterMutex);
            if (--_counter == 0)
            {
                mysql_library_end();
            }
        }

    };

    DB* MySqlDB::clone()const
    {
        MySqlDB* copy = new MySqlDB(this->s_username,this->s_password,this->s_db_name,this->s_serveur,this->_port);
        return copy;
    }
    
    bool MySqlDB::connect()
    {
        dbConn = mysql_init(nullptr);
        if(dbConn == nullptr)
        {
            std::cerr << "Could not get a database driver. Error message: "<< mysql_error(dbConn) <<std::endl;
            return false;
        }

        if(mysql_real_connect(dbConn, s_serveur.c_str(),s_username.c_str(),s_password.c_str(),
                              s_db_name.c_str(), _port, nullptr /* socket*/, 0 /*flags*/) == nullptr)
        {
            std::cerr<< "Could not connect to database. Error message: " <<  mysql_error(dbConn)  << std::endl;
            disconnect();
            return false;
        }

        return true;
    };

    bool MySqlDB::disconnect()
    {
        bool res = false;
        if(dbConn)
        {
            mysql_close(dbConn);
            dbConn = nullptr;
            res = true;
        }
        return res;
    };

    void MySqlDB::threadInit()
    {
        mysql_thread_init();
    }

    void MySqlDB::threadEnd()
    {
        mysql_thread_end();
    }

    Query* MySqlDB::query(const std::string& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->prepared = false;
        return q;
    };

    Query* MySqlDB::query(std::string&& str)
    {
        return query(str);
    };


    Query* MySqlDB::prepareQuery(const std::string& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->prepared = true;

        return q;
    };

    Query* MySqlDB::prepareQuery(std::string&& str)
    {
        return prepareQuery(str);
    }

    bool MySqlDB::create(const std::string& table,const std::vector<const VAttr*>& attrs)
    {
        std::string sql = "CREATE TABLE "+escapeColumn(table)+"(\n";
        unsigned int size = attrs.size();
        sql+= creator().autoField("pk");

        const DB& db=*this;
        for(unsigned int i=0;i<size;++i)
        {
            sql+=",\n"+attrs[i]->create(db);
        }
        sql+="\n)";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    bool MySqlDB::drop(const std::string& table)
    {
        std::string sql = "DROP TABLE "+escapeColumn(table);

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    bool MySqlDB::clear(const std::string& table)
    {

        std::string sql = "TRUNCATE "+escapeColumn(table);

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    /************** PROTECTED **********************/
    
    void MySqlDB::beginTransaction()
    {
        Query* q = this->query("START TRANSACTION");
        q->execute();
        q->next();
        delete q;
    };

    void MySqlDB::endTransaction()
    {
        Query* q = this->query("COMMIT");
        q->execute();
        q->next();
        delete q;

    };

    void MySqlDB::rollback()
    {
        Query* q = this->query("ROLLBACK");
        q->execute();
        q->next();
        delete q;
    };

    int MySqlDB::getLastInsertPk()
    {
        Query& q = *query("SELECT LAST_INSERT_ID()");

        q.execute();
        q.next();

        int pk = -1;
        q.get(pk,getInitialGetcolumnNumber());

        delete &q;

        return pk;
    }

    std::string MySqlDB::escapeColumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int MySqlDB::getInitialGetcolumnNumber() const
    {
        return 0;
    }

    int MySqlDB::getInitialSetcolumnNumber() const
    {
        return 0;
    }

    std::string MySqlDB::limit(const int& skip,const int& count)const
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
    
    const TableCreator& MySqlDB::creator() const
    {
        return my_creator;
    }
    
};
