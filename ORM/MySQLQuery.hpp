#ifndef ORM_MYSQLQUERY_HPP
#define ORM_MYSQLQUERY_HPP

#include <cppconn/resultset.h>

#include "Query.hpp"

namespace orm
{
    class MySQLBdd;

    class MySQLQuery : public Query
    {
        public:
            MySQLQuery(Bdd* bdd);
            MySQLQuery(Bdd* bdd,const std::string& query);
            MySQLQuery(Bdd* bdd,std::string&& query);

            MySQLQuery(const MySQLQuery&) = delete;
            MySQLQuery& operator=(const MySQLQuery&) = delete;
            
            ~MySQLQuery();

            virtual MySQLQuery& orderBy(const std::string& colum,char order='+');
            virtual MySQLQuery& join(const std::string& colum,const Query& other);
            virtual int count()const;
            
            virtual bool get(bool& value,const std::string& colum)const;

            virtual bool get(int& value,const std::string& colum)const;
            virtual bool get(unsigned int& value,const std::string& colum)const;

            virtual bool get(long long int& value,const std::string& colum)const;
            virtual bool get(long long unsigned int& value,const std::string& colum)const;

            virtual bool get(float& value,const std::string& colum)const;
            virtual bool get(long double& value,const std::string& colum)const;

            virtual bool get(std::string& value,const std::string& colum)const;
            
        
        protected:
            virtual bool next();

        private:
            friend class MySQLBdd;
            sql::ResultSet  *bdd_res;    // Create a pointer to a ResultSet object to hold the results of any queries we run
    };
};

#endif
