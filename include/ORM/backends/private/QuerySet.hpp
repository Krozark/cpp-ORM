#ifndef ORM_QUERYSET_HPP
#define ORM_QUERYSET_HPP

#include <ORM/backends/private/VFilter.hpp>
#include <ORM/core/Cache.hpp>
#include <memory>

namespace orm
{
    template<typename T> class SQLObject;
    template<typename T,typename U> class ManyToMany;

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
             * \brief Destructor
             **/
            ~QuerySet();

            /**
             * \brief Construct a filter to apply in the query
             *
             * \param value The value to compare with
             * \param The operator to use see Bdd::Operators for detail
             * \param column The column to apply the comparasion
             * \param args If more than one collum is send, all column will be concatenate (with the correct format) to create the correct column name. Args must be std::string
             * \return *this
             **/
            template<typename U,typename ... Args>
            QuerySet<T>& filter(const U& value,const std::string& operande,const std::string& column,const Args& ... args);

            /**
             * \brief Add a order by constrait to the query
             *
             * \param column The column to use for ordering
             * \param oder The column ordering ( +=ASC or -=DESC)
             *
             * \return *this;
             **/
            QuerySet<T>& orderBy(const std::string& column,const char order='+');

            /**
             * \brief Add a order by constrait to the query
             *
             * \param column The column to use for ordering
             * \param oder The column ordering ( +=ASC or -=DESC)
             *
             * \return *this;
             **/
            QuerySet<T>& orderBy(std::string&& column,const char order='+');
            //QuerySet& orderBy(int,const std::string& column);

            /**
             * \brief Add a negatide filter to the query
             *
             * \param value The value to compare with
             * \param The operator to use see Bdd::Operators for detail
             * \param column The column to apply the comparasion
             * \param args If more than one collum is send, all column will be concatenate (with the correct format) to create the correct column name. Args must be std::string
             *
             * \return *this
             **/
            template<typename U,typename ... Args>
            QuerySet<T>& exclude(const U& value,const std::string& operande,const std::string& column,const Args& ... args);

            /**
             * \brief Add a limit of the number of object return by the dbtabase
             *
             * \param count Maximun number of object
             *
             * \return *this
             **/
            QuerySet<T>& limit(const unsigned int& count);

            /**
             * \brief Add a limit of the number of object return by the dbtabase.
             *
             * .limit(2,5) will return up to 5 (0~5) objects after the execution of the query.
             *
             * \param skip Skip the first <skipe> objects
             * \param count Maximun range of object to return
             *
             * \return *this
             **/
            QuerySet<T>& limit(const unsigned int& skip,const unsigned int& count);

            //QuerySet& aggregate();

            /**
             * \brief Execute tho query and return the coresponding object
             *
             * \param obj Where the result will be stored. If mor than one object are return by the databse, only the fist is construct
             * \param max_depth the maximun recursion depth for the object construction (for fk)
             *
             * \return false if no object match with the query.
             **/
            bool get(T& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief Execute tho query and return the list list of objects
             *
             * \param obj Where the results will be stored. The objects are added to the list.
             * \param max_depth the maximun recursion depth for the object construction (for fk)
             *
             * \return Number of objects
             **/
            int get(typename std::list<std::shared_ptr<T>>& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief Print the content of the filter for debug help
             **/
            void __print__() const;


        private:
            friend class SQLObject<T>;
            template<typename U,typename V> friend class ManyToMany;

            /**
             * \brief Construct a empty QuerySet
             **/
            explicit QuerySet();

            /**
             * \brief Merge column name to build the alias
             *
             * \param prefix The prefix column alias
             * \param column  The column alias to merge
             * \param args Some optional column alias
             *
             * \return the complet alias
             **/
            template<typename ... Args>
            static std::string makecolumname(const std::string& prefix,const std::string& column,Args&& ... args);

            /**
             * \brief Do nothing
             *
             * \param column  The column alias to merge
             *
             * \return column
             **/
            static std::string makecolumname(const std::string& prefix,const std::string& column);

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

            std::list<VFilter*> filters; ///< Store all the filters
            std::list<VFilter*> excludes;///< Store all the negative filters
            std::vector<std::string> order_by; ///< store the column name for ordering
            int limit_skip, ///< skip limit (default is 0)
                limit_count; ///< skip limit (default is all)
    };
}
/***
 * \todo make query like:
 * SELECT SUM(`sort`.`niveau_max`) AS `niveau_max__sum` FROM `sort` WHERE (...)
 * SELECT AVG(`website_sort`.`niveau_max`) AS `niveau_max__avg`, SUM(`website_sort`.`niveau_max`) AS `niveau_max__sum` FROM `website_sort` WHERE (`website_sort`.`passif` = 0  AND `website_sort`.`niveau_max` >= 2 )
 * AVG, SUM, MIN, MAX
 **/
/*template<typename T>
  QuerySet<T>& QuerySet<T>::aggregate()
  {
  std::cerr<<"[todo]: queryset<t>::agregate()"<<std::endl;
  return *this;
  };*/
#include <ORM/backends/private/QuerySet.tpl>
#endif
