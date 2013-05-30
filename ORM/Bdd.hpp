#ifndef ORM_BDD_HPP
#define ORM_BDD_HPP

#include "debug.hpp"

#include <string>
#include <unordered_map>
#include <vector>

/* Abstract class to deal with any database */

namespace orm
{
    class Query;
    class SQLObjectBase;
    template<typename T> class SQLObject;
    class VAttr;

    class Bdd
    {
        public:
            Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port);
            
            Bdd(const Bdd&) = delete;
            Bdd& operator=(const Bdd&) = delete;
            
            virtual bool connect() = 0;
            virtual bool disconnect() = 0;


            /* manualy create  a query */
            virtual Query* query()= 0;
            virtual Query* query(const std::string&) = 0;
            virtual Query* query(std::string&&) = 0;

            /* manualy create  a query */
            virtual Query* prepareQuery(const std::string&) = 0;
            virtual Query* prepareQuery(std::string&&) = 0;


            /* The user defined default bdd to use */
            //static Bdd* Default;
            static Bdd& Default;

            const std::string& operator[](const std::string& key);

            bool save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs);
            bool update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs);
            bool del(const std::string& table,const int& pk);

            virtual std::string escape_colum(const std::string&);
            virtual std::string escape_value(const std::string&);


        protected:
            friend class Query;
            /* Info for connection */
            const std::string s_username;
            const std::string s_password;
            const std::string s_bdd_name;
            const std::string s_serveur;
            const std::string s_port;
            /* Operaters to use you must define:
             * "exact"
             * "iexact"
             * "contains"
             * "icontains"
             * "regex"
             * "iregex"
             * "gt"
             * "gte"
             * "lt"
             * "lte"
             * "startswith"
             * "endswith"
             * "istartswith"
             * "iendswith" */
            std::unordered_map<std::string,std::string> operators;
            /* Execute a query */
            virtual bool executeQuery(Query& query) = 0;
            virtual int getLastInsertPk() = 0;

    };
};

#endif
