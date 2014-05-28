#ifndef ORM_SQLITE3DB_HPP
#define ORM_SQLITE3DB_HPP

#include <ORM/backends/DB.hpp>
#include <ORM/backends/Sqlite3/Sqlite3TableCreator.hpp>

#include <sqlite3.h>

namespace orm
{
    class Sqlite3Query;

    /**
     * \brief Class to deal with Sqlite3 databas
     **/
    class Sqlite3DB : public DB
    {
        public:
            /**
            * \brief Create  a Database connection from filename
            *
            * \param db Database name to use
            **/
            Sqlite3DB(std::string db);

            /**
             * \brief Destructor
             **/
            ~Sqlite3DB();
            
            Sqlite3DB(const Sqlite3DB&) = delete;
            Sqlite3DB& operator=(const Sqlite3DB&) = delete;


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
            virtual const TableCreator& creator()const;

        protected:
            friend class Sqlite3Query;

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
            virtual std::string limit(const int& skip,const int& count) const;


        private:
            sqlite3 * dbConn; ///< Create a pointer to a database connection object

            static Sqlite3TableCreator my_creator;
    };
};
#endif