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
    template<typename T> class FK;
    template<typename T> class Attr;

    class Query
    {
        public:
            Query(Bdd* bdd);
            Query(Bdd* bdd,const std::string& query);
            Query(Bdd* bdd,std::string&& query);

            Query(const Query&) = delete;
            Query& operator=(const Query&) = delete;

            virtual ~Query();

            virtual Query& limit(const unsigned int& limit);

            virtual Query& orderBy(const std::string& colum,char order='+') = 0;
            virtual Query& join(const std::string& colum,const Query& other) = 0;
            virtual int count()const = 0;

            virtual bool get(bool& value,const std::string& colum)const = 0;
            virtual bool get(int& value,const std::string& colum)const = 0;
            virtual bool get(unsigned int& value,const std::string& colum)const = 0;
            virtual bool get(long long int& value,const std::string& colum)const = 0;
            virtual bool get(long long unsigned int& value,const std::string& colum)const = 0;
            virtual bool get(float& value,const std::string& colum)const = 0;
            virtual bool get(long double& value,const std::string& colum)const = 0;
            virtual bool get(std::string& value,const std::string& colum)const = 0;


            /* construct objects from the query result and the number of object created */
            template<typename T>
            int getObj(T& obj,int max_depth);

            template<typename T>
            int getObj(std::list<std::shared_ptr<T>>& objs);

            friend std::ostream& operator<<(std::ostream& output,const Query* self)
            {
                output<<self->query;
                return output;
            };

        protected:
            friend class Bdd;
            friend class MySQLBdd;
            template<typename T> friend class Attr;
            template<typename T> friend class FK;
            /* query as string */
            std::string query;
            /* where to execute the query */
            Bdd* bdd;
    
            /* whene the query have been execute, for parse each raw */
            virtual bool next() = 0;
            
            /* for prepared query */
            virtual bool set(const bool& value,const unsigned int& colum) = 0;
            virtual bool set(const int& value,const unsigned int& colum) = 0;
            virtual bool set(const unsigned int& value,const unsigned int& colum) = 0;
            virtual bool set(const long long int& value,const unsigned int& colum) = 0;
            virtual bool set(const long long unsigned int& value,const unsigned int& colum) = 0;
            virtual bool set(const float& value,const unsigned int& colum) = 0;
            virtual bool set(const long double& value,const unsigned int& colum) = 0;
            virtual bool set(const std::string& value,const unsigned int& colum) = 0;

            bool prepared;

        private:
            bool execute();
            bool executed;
    };
};
#include <ORM/backends/Query.tpl>

#endif
