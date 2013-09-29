#ifndef ORM_MYSQLBDD_HPP
#define ORM_MYSQLBDD_HPP

#include <ORM/backends/Bdd.hpp>

#include <cppconn/driver.h>
#include <cppconn/statement.h>

namespace orm
{
    class MySQLQuery;

    /**
     * \brief Class to deal with Mysql database
     **/
    class MySQLBdd : public Bdd
    {
        public:
            /**
            * \brief Create  a Database connextion
            *
            * \param username Username to use
            * \param pass Password of the user
            * \param bdd Database name to use
            * \param serveur IP adresse of the serveur to connect (default value is 127.0.0.1 as the default for mytsql)
            * \param port Port to use for the connextion (the default is 3306 as the default of mysql)
            **/
            MySQLBdd(std::string username,std::string pass,std::string bdd,std::string serveur="tcp://127.0.0.1",std::string port="3306");

            /**
             * \brief Destructor
             **/
            ~MySQLBdd();
            
            MySQLBdd(const MySQLBdd&) = delete;
            MySQLBdd& operator=(const MySQLBdd&) = delete;

            /**
            * \brief Create the connextion with the database
            *
            * \return false if the connextion fail
            **/
            virtual bool connect();
            /**
            * \brief Close the connextion with the database
            *
            * \return false if fail
            **/
            virtual bool disconnect();

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual /*MySQL*/Query* query(const std::string&);

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual /*MySQL*/Query* query(std::string&&);

            /* manualy create  a query */
            /**
            * \brief Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(const std::string&);

            /**
            * \brief Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(std::string&&);

        
        protected:
            friend class MySQLQuery;

            /**
            * \brief Get the pk of the last object created in the database
            *
            * \return The pk
            **/
            virtual int getLastInsertPk();

            /**
            * \brief Escape the String with "`"
            *
            * \param column column name to escape
            *
            * \return The escaped column name
            *
            * \see escapeValue
            **/
            virtual std::string escapeColumn(const std::string&) const;

            /**
            * \return Return the initial column number for extract values (0 or 1)
            */
            int virtual getInitialGetcolumnNumber() const;

            /**
             * \brief Because limit syntaxe is not the same in all DBMS we need to define it for each one
             *
             * Note : limit(<skip>,<count>) is translante to : "LIMIT [<skip>,]<count>" or "LIMIT <count> [offset <skip>]" for Mysql, Sqlite, Postresql 
             *
             * \param skip Number of object to skip
             * \param count Maximum number of object to return
             *
             * \return *this
             **/
            virtual std::string limit(const int& skip,const int& count)const;


        private:
            sql::Driver     *driver; ///< Create a pointer to a MySQL driver object
            sql::Connection *dbConn; ///< Create a pointer to a database connection object
    };
};

#endif
