#ifndef ORM_MYSqlQUERY_HPP
#define ORM_MYSqlQUERY_HPP

#include <mysql.h>

#include <string>

#include <ORM/backends/Query.hpp>

namespace orm
{
    class MySqlDB;

    /**
     * \brief Abstract class to manage query with Mysql only
     **/
    class MySqlQuery : public Query
    {
        public:

            /**
             * \brief Destructor
             **/
            ~MySqlQuery();
            
        protected:
            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            MySqlQuery(DB& db,const std::string& query);


            MySqlQuery(const MySqlQuery&) = delete;
            MySqlQuery& operator=(const MySqlQuery&) = delete;

            /**
             * \brief Count the number of object returned by the batabase
             *
             * \return  The number of objects
             **/
            virtual int _count()const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(bool& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(int& value,const int& column)const override;

            /**
             * \brief Get a value of a PK/FK collumn, and stor it
             *
             * \param value : where the value is stored (<=0 if null)
             * \param colun The column to extract
             *
             * \return false if fail or column is null
             */
            virtual bool _getPk(int& value, const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(unsigned int& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(long long int& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(long long unsigned int& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(float& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(double& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(long double& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(std::string& value,const int& column)const override;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool _get(struct tm& value,const int& column)const override;


            /**
             * \brief Whene the query have been execute, for loop in results
             *
             * \results fails if fail
             **/
            virtual bool _next() override;

            /* for prepared query */
            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const bool& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const int& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const unsigned int& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const long long int& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const long long unsigned int& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const float& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const double& value,const unsigned int& column) override;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const long double& value,const unsigned int& column) override;

            /**
             *
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const std::string& value,const unsigned int& column) override;
            /**
             *
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _set(const struct tm& value, const unsigned int& colum) override;

            /**
             * \brief For prepared query only, set the column value to null
             *
             * \param value Not use. Allow overload only
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool _setNull(const int& value,const unsigned int& column) override;

            /**
            * \brief Execute a query
            *
            * \return false if faild
            * */
            virtual void _executeQuery() override;


        private:
            friend class MySqlDB;

            MYSQL_RES  *_dbRes; ///< Create a pointer to a ResultSet object to hold the results of any queries we run
            MYSQL_ROW _currentRes;

            struct ResultData
            {
                std::string buffer;
                my_bool is_null;
                long unsigned int real_len;
            };

            std::vector<MYSQL_BIND> _preparedParams;
            std::vector<ResultData> _preparedParamsBuffer;

            mutable std::vector<MYSQL_BIND> _preparedResults;
            mutable std::vector<ResultData> _preparedResultsBuffer;
            int _numFieldsRes;

            MYSQL_STMT *_preparedStatement;///< Hold the statement

            bool _initResults();

            void _resizePreparedParams(unsigned int size);

            template<typename T>
            bool _getValue(T& value,const int& column)const;
    };

/*enum enum_field_types { MYSQL_TYPE_DECIMAL, MYSQL_TYPE_TINY,
			MYSQL_TYPE_SHORT,  MYSQL_TYPE_LONG,
			MYSQL_TYPE_FLOAT,  MYSQL_TYPE_DOUBLE,
			MYSQL_TYPE_NULL,   MYSQL_TYPE_TIMESTAMP,
			MYSQL_TYPE_LONGLONG,MYSQL_TYPE_INT24,
			MYSQL_TYPE_DATE,   MYSQL_TYPE_TIME,
			MYSQL_TYPE_DATETIME, MYSQL_TYPE_YEAR,
			MYSQL_TYPE_NEWDATE, MYSQL_TYPE_VARCHAR,
			MYSQL_TYPE_BIT,
			MYSQL_TYPE_TIMESTAMP2,
			MYSQL_TYPE_DATETIME2,
			MYSQL_TYPE_TIME2,
                        MYSQL_TYPE_NEWDECIMAL=246,
			MYSQL_TYPE_ENUM=247,
			MYSQL_TYPE_SET=248,
			MYSQL_TYPE_TINY_BLOB=249,
			MYSQL_TYPE_MEDIUM_BLOB=250,
			MYSQL_TYPE_LONG_BLOB=251,
			MYSQL_TYPE_BLOB=252,
			MYSQL_TYPE_VAR_STRING=253,
			MYSQL_TYPE_STRING=254,
			MYSQL_TYPE_GEOMETRY=255
    */

}
//https://dev.mysql.com/doc/refman/5.6/en/c-api-prepared-statement-type-codes.html

#endif
