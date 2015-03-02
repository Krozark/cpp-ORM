#ifndef ORM_MYSqlDB_HPP
#define ORM_MYSqlDB_HPP

#include <ORM/backends/DB.hpp>
#include <ORM/backends/MySql/MySqlTableCreator.hpp>

#include <cppconn/driver.h>
#include <cppconn/statement.h>

namespace orm
{
    class MySqlQuery;

    /**
     * \brief Class to deal with Mysql database
     **/
    class MySqlDB : public DB
    {
        public:
            /**
            * \brief Create  a Database connection
            *
            * \param username Username to use
            * \param pass Password of the user
            * \param db Database name to use
            * \param serveur IP adresse of the serveur to connect (default value is 127.0.0.1 as the default for mytsql)
            * \param port Port to use for the connection (the default is 3306 as the default of mysql)
            **/
            MySqlDB(std::string username,std::string pass,std::string db,std::string serveur="tcp://127.0.0.1",std::string port="3306");

            /**
             * \brief Destructor
             **/
            ~MySqlDB();
            
            MySqlDB(const MySqlDB&) = delete;
            MySqlDB& operator=(const MySqlDB&) = delete;
            
            /**
             * \brief Mkae an explitit copy of the connection
             */
            virtual DB* clone()const;

            /**
            * \brief Create the connection with the database
            *
            * \return false if the connection fail
            **/
            virtual bool connect();
            /**
            * \brief Close the connection with the database
            *
            * \return false if fail
            **/
            virtual bool disconnect();

            /**
             * \brief Must be call in a thread
             */
            virtual void threadInit();

            /**
             * \brief Must be call after a end of thread
             */
            virtual void threadEnd();


            /**
             * \brief Begin transaction
             */
            virtual void beginTransaction();

            /**
             * \brief END transaction
             */
            virtual void endTransaction();

            /**
             * \brief rollback
             */
            virtual void rollback();

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual /*MySql*/Query* query(const std::string&);

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual /*MySql*/Query* query(std::string&&);

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

            /**
             * \brief create a table
             * \param table the table name
             * \param attrs the attrubuts list
             */
            virtual bool create(const std::string& table,const std::vector<const VAttr*>& attrs);

            /**
             * \brief drop a table
             */
            virtual bool drop(const std::string& table);
            
            /**
             * \brief drop a table
             */
            virtual bool clear(const std::string& table);

            /**
             * \return the creator object
             * Use it to create column in the database
             */
            virtual const TableCreator& creator() const ;

        
        protected:
            friend class MySqlQuery;

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
            sql::Driver     *driver; ///< Create a pointer to a MySql driver object
            sql::Connection *dbConn; ///< Create a pointer to a database connection object

            static MySqlTableCreator my_creator;
    };
};
#endif
