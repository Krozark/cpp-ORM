#include  <ORM/backends/Sqlite3/Sqlite3Bdd.hpp>
#include  <ORM/backends/Sqlite3/Sqlite3Query.hpp>

#include <ORM/fields/private/VAttr.hpp>


namespace orm
{
    Sqlite3TableCreator Sqlite3Bdd::my_creator;

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

    Bdd* Sqlite3Bdd::clone()const
    {
        Sqlite3Bdd* copy = new Sqlite3Bdd(this->s_bdd_name);
        return copy;
    }
    
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

    void Sqlite3Bdd::threadInit()
    {
    };

    void Sqlite3Bdd::threadEnd()
    {
    };

    Query* Sqlite3Bdd::query(const std::string& str)
    {
        return new Sqlite3Query(*this,str);
    };

    Query* Sqlite3Bdd::query(std::string&& str)
    {
        return new Sqlite3Query(*this,str);
    };


    Query* Sqlite3Bdd::prepareQuery(const std::string& str)
    {
        Sqlite3Query* q = new Sqlite3Query(*this,str);
        q->prepared = true;
        return q;
    };

    Query* Sqlite3Bdd::prepareQuery(std::string&& str)
    {
        Sqlite3Query* q = new Sqlite3Query(*this,str);
        q->prepared = true;
        return q;
    }

    bool Sqlite3Bdd::create(const std::string& table,const std::vector<const VAttr*>& attrs)
    {
        std::string sql = "CREATE TABLE \""+table+"\"(\n";
        unsigned int size = attrs.size();

        if(size>0)
        {
            Bdd& bdd=*this;
            sql+=attrs[0]->create(bdd);
            for(unsigned int i=1;i<size;++i)
            {
                sql+=",\n"+attrs[i]->create(bdd);
            }
        }
        sql+="\n);";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    };
    
    bool Sqlite3Bdd::drop(const std::string& table)
    {
        std::string sql = "DROP TABLE \""+table+"\";";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    /************** PROTECTED **********************/

    void Sqlite3Bdd::beginTransaction()
    {
        Query* q = this->query("BEGIN TRANSACTION;");
        q->execute();
        q->next();
        delete q;
    };

    void Sqlite3Bdd::endTransaction()
    {
        Query* q = this->query("END TRANSACTION;");
        q->execute();
        q->next();
        delete q;
    };

    void Sqlite3Bdd::rollback()
    {
        Query* q = this->query("ROLLBACK;");
        q->execute();
        q->next();
        delete q;
    };


    int Sqlite3Bdd::getLastInsertPk()
    {
        return (int)sqlite3_last_insert_rowid(dbConn);
    }

    std::string Sqlite3Bdd::escapeColumn(const std::string& str) const
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

    const TableCreator& Sqlite3Bdd::creator()const
    {
        return my_creator;
    }
};
