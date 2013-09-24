#ifndef ORM_MYSQLBDD_HPP
#define ORM_MYSQLBDD_HPP

#include <ORM/backends/Bdd.hpp>

#include <cppconn/driver.h>
#include <cppconn/statement.h>

namespace orm
{
    class MySQLQuery;

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
            * \return NULL if faild.
            **/
            virtual /*MySQL*/Query* query();
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
            * \breif Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(const std::string&);

            /**
            * \breif Create a prepared query to execute
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
            * \param colum Colum name to escape
            *
            * \return The escaped colum name
            *
            * \see escapeValue
            **/
            virtual std::string escapeColum(const std::string&) const;
            
        private:
            sql::Driver     *driver; ///< Create a pointer to a MySQL driver object
            sql::Connection *dbConn; ///< Create a pointer to a database connection object
    };
};

#endif
