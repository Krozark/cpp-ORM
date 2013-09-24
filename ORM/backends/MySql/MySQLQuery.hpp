#ifndef ORM_MYSQLQUERY_HPP
#define ORM_MYSQLQUERY_HPP

#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include <ORM/backends/Query.hpp>

namespace orm
{
    class MySQLBdd;

    /**
     * \brief Abstract class to manage query with Mysql only
     **/
    class MySQLQuery : public Query
    {
        //public:
        protected:
            /**
             * \brief Create a empty query
             *
             * \param bdd database where the query will be execute
             **/
            MySQLQuery(Bdd* bdd);
            
            /**
             * \brief Create a query
             *
             * \param bdd database where the query will be execute
             * \param query Query string to execute
             **/
            MySQLQuery(Bdd* bdd,const std::string& query);

            /**
             * \brief Create a query
             *
             * \param bdd database where the query will be execute
             * \param query Query string to execute
             **/
            MySQLQuery(Bdd* bdd,std::string&& query);

            MySQLQuery(const MySQLQuery&) = delete;
            MySQLQuery& operator=(const MySQLQuery&) = delete;
            
            ~MySQLQuery();

            /**
             * \brief Because limit syntaxe is not the same in all DBMS we need to define it for each one
             *
             * Note : limit(<skip>,<count>) is translante to : "LIMIT [<skip>,]<count>" 
             *
             * \param skip Number of object to skip
             * \param count Maximum number of object to return
             *
             * \return *this
             **/
            virtual MySQLQuery& limit(const int& skip,const int& count);

            /**
             * \brief Count the number of object returned by the batabase
             *
             * \return  The number of objects
             **/
            virtual int count()const;
            
            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(bool& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(int& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(unsigned int& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long int& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long unsigned int& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(float& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long double& value,const int& colum)const;

            /**
             * \brief Get a value of a colum, and store it 
             *
             * \param colun The colum to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(std::string& value,const int& colum)const;
           
        
            /**
             * \brief Whene the query have been execute, for loop in results
             *
             * \results fals if fail 
             **/
            virtual bool next();

            /* for prepared query */
            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const bool& value,const unsigned int& colum);

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const int& value,const unsigned int& colum);

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const unsigned int& value,const unsigned int& colum);

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long int& value,const unsigned int& colum);

            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long unsigned int& value,const unsigned int& colum);
            
            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const float& value,const unsigned int& colum);
            
            /**
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long double& value,const unsigned int& colum);

            /**
             *
             * \brief For prepared query only, set the colum value
             *
             * \param value The value to set
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool set(const std::string& value,const unsigned int& colum);
            
            /**
             * \brief For prepared query only, set the colum value to null
             *
             * \param value Not use. Allow overload only
             * \param colum The colum number to set
             *
             * \results false if fail
             **/
            virtual bool setNull(const int& value,const unsigned int& colum);

            /**
            * \brief Execute a query
            *
            * \return false if faild
            * */
            virtual bool executeQuery();


        private:
            friend class MySQLBdd;
            sql::ResultSet  *bdd_res; ///< Create a pointer to a ResultSet object to hold the results of any queries we run
            sql::PreparedStatement *prepared_statement; ///< Hold the statement
            sql::Statement  *statement; ///< Create a pointer to a Statement object to hold our SQL commands
    };
};
/* sql::DataType (mysql)
 * 	enum {
		UNKNOWN = 0,
		BIT,
		TINYINT,
		SMALLINT,
		MEDIUMINT,
		INTEGER,
		BIGINT,
		REAL,
		DOUBLE,
		DECIMAL,
		NUMERIC,
		CHAR,
		BINARY,
		VARCHAR,
		VARBINARY,
		LONGVARCHAR,
		LONGVARBINARY,
		TIMESTAMP,
		DATE,
		TIME,
		YEAR,
		GEOMETRY,
		ENUM,
		SET,
		SQLNULL
	};*/

#endif
