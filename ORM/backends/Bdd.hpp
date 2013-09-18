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
    template<typename T> class SQLObject;
    template<typename T> class QuerySet;
    template<typename T,typename U> class ManyToMany;
    class VAttr;

    /**
     * \brief Abstract class to deal with any database 
     **/
    class Bdd
    {
        public:
            /**
            * \brief Create  a Database connextion
            *
            * \param username Username to use
            * \param pass Password of the user
            * \param bdd Database name to use
            * \param serveur IP adresse of the serveur to connect
            * \param port Port to use for the connextion
            **/
            Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port);

            virtual ~Bdd();

            Bdd(const Bdd&) = delete;
            Bdd& operator=(const Bdd&) = delete;
                
            /**
            * \brief Create the connextion with the database
            *
            * \return false if the connextion fail
            **/
            virtual bool connect() = 0;

            /**
            * \brief Clase the connextion with the database
            *
            * \return false if fail
            **/
            virtual bool disconnect() = 0;


                /* manualy create  a query */

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \return NULL if faild.
            **/
            virtual Query* query()= 0;

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
            * \breif Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(const std::string&) = 0;

            /**
            * \breif Create a prepared query to execute
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


        protected:
            friend class Query;
            friend class SQLObjectBase;
            template<typename T> friend class SQLObject;
            template<typename T> friend class QuerySet;
            template<typename T,typename U> friend class ManyToMany;

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
            * \brief Execute a query
            *
            * \return false if faild
            * */
            virtual bool executeQuery(Query& query) = 0;

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
            * \param attrs Colum of the oject to save
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
            * \param attrs Colum of the oject to update
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
            * \param colum Colum name to escape
            *
            * \return The escaped colum name
            *
            * \see escapeValue
            **/
            virtual std::string escapeColum(const std::string& colum) const;

            /**
            * \brief Escape the String
            *
            * \param value  Value to escape
            *
            * \return The escaped value
            *
            * \see escapeColum
            **/
            virtual std::string escapeValue(const std::string& value) const;

            /**
            * \brief format the operation for the database
            *
            * \param ope Operation ("gt","lt","exact" ...)
            * \param value  the value to escape
            *
            * \return The escaped operation
            *
            * \see operators
            **/
            std::string escapeValue(const std::string& ope,const std::string& value) const;
    };
};

#endif
