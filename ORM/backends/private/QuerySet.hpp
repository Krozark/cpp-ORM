#ifndef ORM_QUERYSET_HPP
#define ORM_QUERYSET_HPP

#include <ORM/backends/Filter.hpp>
#include <ORM/core/Cache.hpp>

namespace orm
{
    template<typename T> class SQLObject;

    /**
     * \brief A class that allow you to make query on the type T
     *
     * Note : T must be a SQLObject
     *
     * \see SQLObject
     **/
    template <typename T>
    class QuerySet
    {
        public:
            /**
             * \brief Construct a QuerySet from a tmp value
             *
             * \param tmp the tmp value to use
             *
             * Note : tmp as an undefined status after the call of this function
             **/
            QuerySet(QuerySet<T>&& tmp);

            /**
             * \brief Construct a filter to apply in the query
             *
             * \param value The value to compare with
             * \param The operator to use see Bdd::Operators for detail
             * \param colum The colum to apply the comparasion
             * \param args If more than one collum is send, all colum will be concatenate (with the correct format) to create the correct colum name. Args must be std::string
             * \return *this
             **/
            template<typename U,typename ... Args>
            QuerySet<T>& filter(const U& value,const std::string& operande,const std::string& colum,const Args& ... args);

            /**
             * \brief Add some filters to apply in the query
             *
             * \param filter_list some Filter to apply to the query.
             *
             * \return *this
             **/
            QuerySet<T>& filter(const std::list<Filter>& filter_list);

            /**
             * \brief Add some filters to apply in the query from a tmp value
             *
             * \param filter_list some Filter to apply to the query.
             *
             * \return *this
             *
             * Note : filter_list as an undefined status after the call of this function
             **/
            QuerySet<T>& filter(std::list<Filter>&& filter_list);

            /**
             * \brief Add a order by constrait to the query
             *
             * \param colum The colum to use for ordering
             *
             * \return *this;
             **/
            QuerySet<T>& orderBy(const std::string& colum);

            /**
             * \brief Add a order by constrait to the query
             *
             * \param colum The colum to use for ordering
             *
             * \return *this;
             **/
            QuerySet<T>& orderBy(std::string&& colum);
            //QuerySet& orderBy(int,const std::string& colum);

            /**
             * \brief Add a negatide filter to the query
             *
             * \param value The value to compare with
             * \param The operator to use see Bdd::Operators for detail
             * \param colum The colum to apply the comparasion
             * \param args If more than one collum is send, all colum will be concatenate (with the correct format) to create the correct colum name. Args must be std::string
             *
             * \return *this
             **/
            template<typename U,typename ... Args>
            QuerySet<T>& exclude(const U& value,const std::string& operande,const std::string& colum,const Args& ... args);

            /**
             * \brief Add some negative filters to apply in the query
             *
             * \param filter_list some Filter to apply to the query.
             *
             * \return *this
             **/
            QuerySet<T>& exclude(const std::list<Filter>& exclude_list);

            /**
             * \brief Add some negative filters to apply in the query
             *
             * \param filter_list some Filter to apply to the query.
             *
             * \return *this
             **/
            QuerySet<T>& exclude(std::list<Filter>&& exclude_list);

            /**
             * \brief Add a limite of the number of object return by the dbtabase
             *
             * \param max Maximun number of object
             *
             * \return *this
             **/
            QuerySet<T>& limit(const unsigned int& max);

            /**
             * \brief Add a limite of the number of object return by the dbtabase.
             *
             * .limite(2,5) will return in maximun 3 (5-2) objects after the execution of the query.
             *
             * \param min Minimal range of object
             * \param max Maximun range of object
             *
             *
             *
             * \return *this
             **/
            QuerySet<T>& limit(const unsigned int& min,const unsigned int& max);

            //QuerySet& agregate();

            /**
             * \brief Execute tho query and return the coresponding object
             *
             * \param obj Where the result will be stored. If mor than one object are return by the databse, only the fist is construct
             * \param max_depth the maximun recursion depth for the object construction (for fk)
             *
             * \return false if no object match with the query.
             **/
            bool get(T& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);
            //bool get(typename std::list<Cache<T>::type_ptr>& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief Print the content of the filter for debug help
             **/
            void __print__() const;


        private:
            friend class SQLObject<T>;

            /**
             * \brief Construct a empty QuerySet
             **/
            explicit QuerySet();

            /**
             * \brief Merge colum name to build the alias
             *
             * \param prefix The prefix colum alias
             * \param colum  The colum alias to merge
             * \param args Some optional colum alias
             *
             * \return the complet alias
             **/
            template<typename ... Args>
            static std::string makeColumName(const std::string& prefix,const std::string& colum,Args&& ... args);

            /**
             * \brief Merge colum name to build the alias
             *
             * \param prefix The prefix colum alias
             * \param colum  The colum alias to merge
             * \param args Some optional colum alias
             *
             * \return the complet alias
             **/
            template<typename ... Args>
            static std::string makeColumName(std::string&& prefix,std::string&& colum,Args&& ... args);

            /**
             * \brief Do nothing
             *
             * \param colum  The colum alias to merge
             *
             * \return colum
             **/
            static std::string makeColumName(std::string colum);

            /**
             * \brief Construct the query with all constraints
             *
             * \param max_depth Maximun depth of recursion in join (if object have FK only)
             *
             * \return NULL if fail or the query to use in othe case
             **/
            Query* makeQuery(int max_depth);


            QuerySet(const QuerySet&) = delete;
            QuerySet& operator=(const QuerySet&) = delete;

            std::list<Filter> filters; ///< Store all the filters
            std::list<Filter> excludes;///< Store all the negative filters
            std::vector<std::string> order_by; ///< store the colum name for ordering
            int limit_min, ///< minimun limite (default is none)
                limit_max; ///< maximun limite (default is none)
    };
}
#include <ORM/backends/private/QuerySet.tpl>
#endif
