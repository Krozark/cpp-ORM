#include  <ORM/backends/Sqlite3/Sqlite3DB.hpp>
#include  <ORM/backends/Sqlite3/Sqlite3Query.hpp>

#include <ORM/fields/private/VAttr.hpp>
#include <ORM/backends/op.hpp>


namespace orm
{
    Sqlite3TableCreator Sqlite3DB::_creator;

    Sqlite3DB::Sqlite3DB(const std::string& db) :
        DB("","",db,"",0),
        _dbConn(0)
    {


        //operators
        _operators[op::exact]= " = %s";
        _operators[op::iexact]= " LIKE %s ESCAPE '\\'";
        _operators[op::contains]= " LIKE %s ESCAPE '\\'";
        _operators[op::icontains]= " LIKE %s ESCAPE '\\'";
        _operators[op::regex]= " REGEXP %s";
        _operators[op::iregex]= " REGEXP '(?i)' || %s";
        _operators[op::gt]= " > %s";
        _operators[op::gte]= " >= %s";
        _operators[op::lt]= " < %s";
        _operators[op::lte]= " <= %s";
        _operators[op::startswith]= " LIKE %s ESCAPE '\\'";
        _operators[op::endswith]= " LIKE %s ESCAPE '\\'";
        _operators[op::istartswith]= " LIKE %s ESCAPE '\\'";
        _operators[op::iendswith]= " LIKE %s ESCAPE '\\'";

        //ordering
        _operators["?"] = "RANDOM() ";
        _operators["+"] = "ASC ";
        _operators["-"] = "DESC ";

    };

    Sqlite3DB::~Sqlite3DB()
    {
        if(_dbConn)
        {
            sqlite3_close(_dbConn);
        }
    };

    DB* Sqlite3DB::clone()const
    {
        Sqlite3DB* copy = new Sqlite3DB(this->_dbName);
        return copy;
    }

    bool Sqlite3DB::connect()
    {
        /* open the database */
        int result=sqlite3_open(_dbName.c_str(),&_dbConn);
        if (result != SQLITE_OK)
        {
            ORM_PRINT_ERROR("Sqlite3DB::connect() Failed to open database ")
            sqlite3_close(_dbConn);
            return false;
        }

        return true;
    };

    bool Sqlite3DB::disconnect()
    {
        int result = sqlite3_close(_dbConn);
        if (result != SQLITE_OK)
        {
            ORM_PRINT_WARNING("Sqlite3DB::disconnect() Failed to close database")
            return false;
        }
        return true;
    };

    void Sqlite3DB::threadInit()
    {
    };

    void Sqlite3DB::threadEnd()
    {
    };

    Query* Sqlite3DB::query(const std::string& str)
    {
        return new Sqlite3Query(*this,str);
    };

    Query* Sqlite3DB::query(std::string&& str)
    {
        return new Sqlite3Query(*this,str);
    };


    Query* Sqlite3DB::prepareQuery(const std::string& str)
    {
        Sqlite3Query* q = new Sqlite3Query(*this,str);
        q->_prepared = true;
        return q;
    };

    Query* Sqlite3DB::prepareQuery(std::string&& str)
    {
        Sqlite3Query* q = new Sqlite3Query(*this,str);
        q->_prepared = true;
        return q;
    }

    bool Sqlite3DB::create(const std::string& table,const std::vector<const VAttr*>& attrs)
    {
        std::string sql = "CREATE TABLE \""+table+"\"(\n";
        unsigned int size = attrs.size();
        sql+= creator().autoField("pk");

        const DB& db=*this;
        for(unsigned int i=0;i<size;++i)
        {
            sql+=",\n"+attrs[i]->create(db);
        }
        sql+="\n);";

        Query* q = this->query(sql);
        q->_execute();
        q->_next();
        delete q;

        return true;
    };

    bool Sqlite3DB::drop(const std::string& table)
    {
        std::string sql = "DROP TABLE \""+table+"\";";

        Query* q = this->query(sql);
        q->_execute();
        q->_next();
        delete q;

        return true;
    }

    bool Sqlite3DB::clear(const std::string& table)
    {

        std::string sql = "DELETE FROM \""+table+"\";";

        Query* q = this->query(sql);
        q->_execute();
        q->_next();
        delete q;

        return true;
    }

    const TableCreator& Sqlite3DB::creator()const
    {
        return _creator;
    }

    /************** PROTECTED **********************/

    void Sqlite3DB::beginTransaction()
    {
        Query* q = this->query("BEGIN TRANSACTION;");
        q->_execute();
        q->_next();
        delete q;
    };

    void Sqlite3DB::endTransaction()
    {
        Query* q = this->query("END TRANSACTION;");
        q->_execute();
        q->_next();
        delete q;
    };

    void Sqlite3DB::rollback()
    {
        Query* q = this->query("ROLLBACK;");
        q->_execute();
        q->_next();
        delete q;
    };


    int Sqlite3DB::_getLastInsertPk()
    {
        return (int)sqlite3_last_insert_rowid(_dbConn);
    }

    std::string Sqlite3DB::_escapeColumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int Sqlite3DB::_getInitialGetcolumnNumber() const
    {
        return 0;
    }

    int Sqlite3DB::_getInitialSetcolumnNumber() const
    {
        return 1;
    }


    std::string Sqlite3DB::_limit(const int& skip,const int& count) const
    {
        std::string query;
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(count)+" OFFEST "+std::to_string(skip);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        #if ORM_VERBOSITY & ORM_WARNING
        else
            ORM_PRINT_WARNING("Sqlite3DB::Limit(skip,count) count can't be <= 0")
        #endif
        return query;
    };


};
