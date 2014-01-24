#ifndef ORM_BDD_HPP
#define ORM_BDD_HPP

#include <ORM/externals.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace orm
{
    class Query;
    class SQLObjectBase;
    class VAttr;
    template<typename T> class SQLObject;
    template<typename T> class QuerySet;
    template<typename T> class FKBase;
    template<typename T> class Cache;
    template<typename T> class Filter;
    template<typename T,typename U> class ManyToMany;
    template<typename T,typename U,typename V> class M2MQuerySet;

    /**
     * \brief Abstract class to deal with any database 
     **/
    class Bdd
    {
        public:
            /**
            * \brief Create  a Database connection
            *
            * \param username Username to use
            * \param pass Password of the user
            * \param bdd Database name to use
            * \param serveur IP adresse of the serveur to connect
            * \param port Port to use for the connection
            **/
            Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port);


            /***
             * \brief Destructor
             **/
            virtual ~Bdd();

            Bdd(const Bdd&) = delete;
            Bdd& operator=(const Bdd&) = delete;


            /**
             * \brief Mkae an explitit copy of the connection
             */
            virtual Bdd* clone()const = 0;
                
            /**
            * \brief Create the connection with the database
            *
            * \return false if the connection fail
            **/
            virtual bool connect() = 0;

            /**
            * \brief Close the connection with the database
            *
            * \return false if fail
            **/
            virtual bool disconnect() = 0;


            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* query(const std::string& query) = 0;

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* query(std::string&&) = 0;

            /**
            * \brief Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(const std::string&) = 0;

            /**
            * \brief Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(std::string&&) = 0;

            /**
            * \brief The user defined default bdd to use
            **/
            static Bdd& Default;


            /**
             * \brief Compare 2 Bdd
             **/
            bool operator==(const Bdd& other) const;


        protected:
            friend class Query;
            friend class SQLObjectBase;
            friend class VAttr;
            template<typename T> friend class SQLObject;
            template<typename T> friend class QuerySet;
            template<typename T> friend class Cache;
            template<typename T> friend class FKBase;
            template<typename T> friend class Filter;
            template<typename T,typename U> friend class ManyToMany;
            template<typename T,typename U,typename V> friend class M2MQuerySet;

            /* Info for connection */
            const std::string s_username; ///< Username use for the connection
            const std::string s_password; ///< Username password use for the connection
            const std::string s_bdd_name; ///< Database  name use for the connection
            const std::string s_serveur; ///< Ip of tfe serveur to make the connection
            const std::string s_port; ///< Port to use for the connection

            /**
            * \brief Map the operators that can be use
            *
            * Operators : "exact", "iexact", "contains", "icontains","regex", "iregex", "gt", "gte", "lt", "lte", "startswith", "endswith", "istartswith", "iendswith"
            * Ordering : "?","+","-"
            **/
            std::unordered_map<std::string,std::string> operators;

            /**
             * \brief Begin transaction
             */
            virtual void beginTransaction() = 0;

            /**
             * \brief END transaction
             */
            virtual void endTransaction() = 0;

            /**
             * \brief rollback
             */
            virtual void rollback() = 0;

            /**
            * \brief Get the pk of the last object created in the database
            *
            * \return The pk
            **/
            virtual int getLastInsertPk() = 0;

            /**
            * \brief Save a object in the database
            *
            * \param table Table of the object
            * \param pk PK of the object to save
            * \param attrs column of the oject to save
            *
            * \return false if fail
            *
            * \see update
            **/
            bool save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs);

            /**
            * \brief Update calum value of a object
            *
            * \param table Table of the object
            * \param pk PK of the object to save
            * \param attrs column of the oject to update
            *
            * \return false if fail
            *
            * \see save
            **/
            bool update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs);

            /**
            * \brief Delete the object
            *
            * \param table Table of the object
            * \param pk PK of the object
            *
            * \return false if fail
            *
            **/
            bool del(const std::string& table,const int& pk);

            /**
            * \brief Escape the String
            *
            * \param column column name to escape
            *
            * \return The escaped column name
            *
            * \see escapeValue
            **/
            virtual std::string escapeColumn(const std::string& column) const;

            /**
            * \brief format the operation for the database
            *
            * \param ope Operation ("gt","lt","exact" ...)
            * \param value  the value to format with the operator (add some '%')
            *
            * \return The formated operation
            *
            * \see operators
            **/
            std::string formatValue(const std::string& ope,std::string value) const;

            /**
            * \brief format the operation for the database
            *
            * \param ope Operation ("gt","lt","exact" ...)
            *
            * \return The formated operation by adding (?) at the right place
            *
            * \see operators
            **/
            std::string formatPreparedValue(const std::string& ope) const;

            /**
             * \return Return the initial column number for extract values (0 or 1)
             */
            int virtual getInitialGetcolumnNumber() const = 0;

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
            virtual std::string limit(const int& skip,const int& count) const = 0;
    };
};
/**
 * \todo data_types = {
  'AutoField':         'integer AUTO_INCREMENT',
  'BooleanField':      'bool',
  'CharField':         'varchar(%(max_length)s)',
  'CommaSeparatedIntegerField': 'varchar(%(max_length)s)',
  'DateField':         'date',
  'DateTimeField':     'datetime',
  'DecimalField':      'numeric(%(max_digits)s, %(decimal_places)s)',
  'FileField':         'varchar(%(max_length)s)',
  'FilePathField':     'varchar(%(max_length)s)',
  'FloatField':        'double precision',
  'IntegerField':      'integer',
  'BigIntegerField':   'bigint',
  'IPAddressField':    'char(15)',
  'GenericIPAddressField': 'char(39)',
  'NullBooleanField':  'bool',
  'OneToOneField':     'integer',
  'PositiveIntegerField': 'integer UNSIGNED',
  'PositiveSmallIntegerField': 'smallint UNSIGNED',
  'SlugField':         'varchar(%(max_length)s)',
  'SmallIntegerField': 'smallint',
  'TextField':         'longtext',
  'TimeField':         'time',
  }*/

#endif
