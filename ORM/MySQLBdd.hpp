#ifndef ORM_MYSQLBDD_HPP
#define ORM_MYSQLBDD_HPP

#include "Bdd.hpp"

#include <cppconn/driver.h>
#include <cppconn/statement.h>

namespace orm
{
    class MySQLQuery;

    class MySQLBdd : public Bdd
    {
        public:
            MySQLBdd(std::string username,std::string pass,std::string bdd,std::string serveur="tcp://127.0.0.1",std::string port="3306");

            ~MySQLBdd();
            
            MySQLBdd(const MySQLBdd&) = delete;
            MySQLBdd& operator=(const MySQLBdd&) = delete;

            virtual bool connect();
            virtual bool disconnect();

            virtual /*MySQL*/Query* query();
            virtual /*MySQL*/Query* query(const std::string&);
            virtual /*MySQL*/Query* query(std::string&&);

            /* manualy create  a query */
            virtual Query* prepareQuery(const std::string&);
            virtual Query* prepareQuery(std::string&&);
        
        protected:
            friend class MySQLQuery;
            virtual bool executeQuery(Query& query);
            virtual int getLastInsertPk();
            virtual std::string escape_colum(const std::string&);
            
        private:
            sql::Driver     *driver; // Create a pointer to a MySQL driver object
            sql::Connection *dbConn; // Create a pointer to a database connection object
            sql::Statement  *statement;   // Create a pointer to a Statement object to hold our SQL commands
    };
};

#endif
