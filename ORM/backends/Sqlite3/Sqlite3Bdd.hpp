#ifndef ORM_SQLITE3BDD_HPP
#define ORM_SQLITE3BDD_HPP

#include <ORM/backends/Bdd.hpp>

#include <sqlite3.h>

namespace orm
{
    class Sqlite3Query;

    class Sqlite3Bdd : public Bdd
    {
        public:
            /**
            * \brief Create  a Database connextion from filename
            *
            * \param bdd Database name to use
            **/
            Sqlite3Bdd(std::string bdd);

            ~Sqlite3Bdd();
            
            Sqlite3Bdd(const Sqlite3Bdd&) = delete;
            Sqlite3Bdd& operator=(const Sqlite3Bdd&) = delete;

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
            virtual /*Sqlite3*/Query* query();
            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual /*Sqlite3*/Query* query(const std::string&);

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual /*Sqlite3*/Query* query(std::string&&);

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
            friend class Sqlite3Query;

            /**
            * \brief Execute a query
            *
            * \return false if faild
            * */
            virtual bool executeQuery(Query& query);

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
            sqlite3 * dbConn; ///< Create a pointer to a database connection object
            /*sql::Driver     *driver; ///< Create a pointer to a Sqlite3 driver object
            sql::Statement  *statement; ///< Create a pointer to a Statement object to hold our SQL commands
            */
    };
};

#endif
