#ifndef ORM_SQLITE3BDD_HPP
#define ORM_SQLITE3BDD_HPP

#include <ORM/backends/Bdd.hpp>

#include <sqlite3.h>

namespace orm
{
    class Sqlite3Query;

    /**
     * \brief Class to deal with Sqlite3 databas
     **/
    class Sqlite3Bdd : public Bdd
    {
        public:
            /**
            * \brief Create  a Database connection from filename
            *
            * \param bdd Database name to use
            **/
            Sqlite3Bdd(std::string bdd);

            /**
             * \brief Destructor
             **/
            ~Sqlite3Bdd();
            
            Sqlite3Bdd(const Sqlite3Bdd&) = delete;
            Sqlite3Bdd& operator=(const Sqlite3Bdd&) = delete;


            /**
             * \brief Mkae an explitit copy of the connection
             */
            virtual Bdd* clone()const;

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
    };
};

/*
    data_types = {
        'AutoField':                    'integer NOT NULL PRIMARY KEY',
        'BooleanField':                 'bool',
        'CharField':                    'varchar(%(max_length)s)',
        'CommaSeparatedIntegerField':   'varchar(%(max_length)s)',
        'DateField':                    'date',
        'DateTimeField':                'datetime',
        'DecimalField':                 'decimal',
        'FileField':                    'varchar(%(max_length)s)',
        'FilePathField':                'varchar(%(max_length)s)',
        'FloatField':                   'real',
        'IntegerField':                 'integer',
        'BigIntegerField':              'bigint',
        'IPAddressField':               'char(15)',
        'GenericIPAddressField':        'char(39)',
        'NullBooleanField':             'bool',
        'OneToOneField':                'integer',
        'PositiveIntegerField':         'integer unsigned',
        'PositiveSmallIntegerField':    'smallint unsigned',
        'SlugField':                    'varchar(%(max_length)s)',
        'SmallIntegerField':            'smallint',
        'TextField':                    'text',
        'TimeField':                    'time',
        BinaryField
        integer NOT NULL REFERENCES "website_aamodification" ("id")
        UNIQUE ("analysemgf_id", "aamodification_id")
    }
*/

#endif
