#ifndef ORM_QUERY_HPP
#define ORM_QUERY_HPP

#include <ORM/backends/Bdd.hpp>

#include <string>
#include <list>
#include <ostream>
#include <memory>

namespace orm
{
    class Bdd;
    class MySQLBdd;
    class Sqlite3Bdd;
    class SQLObjectBase;
    template<typename T> class FKBase;
    template<typename T> class Attr;
    template<typename T> class QuerySet;
    template<typename T> class SQLObject;
    template<typename T> class Cache;

    /**
     * \brief Abstract class to manage query
     **/
    class Query
    {
        protected:
            friend class Bdd;
            friend class MySQLBdd;
            friend class Sqlite3Bdd;
            friend class SQLObjectBase;
            template<typename T> friend class Attr;
            template<typename T> friend class FKBase;
            template<typename T> friend class QuerySet;
            template<typename T> friend class SQLObject;
            template<typename T> friend class Cache;
            /**
             * \brief Create a empty query
             *
             * \param bdd database where the query will be execute
             **/
            Query(Bdd* bdd);

            /**
             * \brief Create a query
             *
             * \param bdd database where the query will be execute
             * \param query Query string to execute
             **/
            Query(Bdd* bdd,const std::string& query);

            /**
             * \brief Create a query
             *
             * \param bdd database where the query will be execute
             * \param query Query string to execute
             **/
            Query(Bdd* bdd,std::string&& query);

            Query(const Query&) = delete;
            Query& operator=(const Query&) = delete;

            virtual ~Query();

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
            virtual Query& limit(const int& skip,const int& count) = 0;


            /**
             * \brief Count the number of object returned by the batabase
             *
             * \return  The number of objects
             **/
            virtual int count()const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum the extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(bool& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(int& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(unsigned int& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long int& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long unsigned int& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(float& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long double& value,const int& colum)const = 0;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(std::string& value,const int& colum)const = 0;


            /**
             * \brief Construct objects from the query. T must be a SQLObject
             *
             * \param obj Where the object will be stored
             * \param max_depth The maximum recursion depth of object construction (for FK)
             *
             * \return the number of object created
             **/
            template<typename T>
            int getObj(T& obj,int max_depth);

            /**
             * \brief Construct objects from the query. T must be a SQLObject
             *
             * \param objs Where the objects will be stored
             * \param max_depth The maximum recursion depth of object construction (for FK)
             *
             * \return the number of object created
             **/
            template<typename T>
            int getObj(std::list<std::shared_ptr<T>>& objs,int max_depth);

            /**
             * \brief Print the content of the query for debug help
             **/
            friend std::ostream& operator<<(std::ostream& output,const Query* self)
            {
                output<<self->query;
                return output;
            };


            std::string query; ///<query as string
            Bdd* bdd; ///< database where the query will be executed
    
            /**
             * \brief Whene the query have been execute, for loop in results
             *
             * \results fals if fail 
             **/
            virtual bool next() = 0;
            
            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const bool& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const int& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const unsigned int& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long int& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long unsigned int& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const float& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long double& value,const unsigned int& colum) = 0;

            /**
             *
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const std::string& value,const unsigned int& colum) = 0;

            /**
             * \brief For prepared query only, set the colum value to null
             *
             * \param value Not use. Allow overload only
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool setNull(const int& value,const unsigned int& colum) = 0;

            bool prepared; ///< is the query is a prepared one?
            virtual bool executeQuery() = 0;

        private:
            /**
             * \brief Execute the query on the database
             *
             * \return false if fail
             **/
            bool execute();

            bool executed; ///< is the query already executed?
    };
};
#include <ORM/backends/Query.tpl>

#endif
