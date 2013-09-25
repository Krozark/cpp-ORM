#ifndef ORM_VFILTER_HPP
#define ORM_VFILTER_HPP

#include <string>

namespace orm
{
    template<typename T> class SQLObject;
    template<typename T> class QuerySet;
    class Query;

    /**
     * \brief A class representing filter in query
     **/
    class VFilter
    {
        public:
            /**
             * \brief Create a filter
             *
             * \param colum Colum where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            VFilter(const std::string& colum,const std::string& ope);

            /**
             * \brief Create a filter
             *
             * \param colum Colum where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            VFilter(std::string&& colum,const std::string& ope);

           
            
            /**
             * \brief Print the content of the filter for debug help
             **/
            virtual void __print__() const = 0;



        protected:
            template<typename T> friend class SQLObject;
            template<typename T> friend class QuerySet;

            const std::string colum;
            const std::string ope;

           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param colum Colum index
            *
            * \return false if fail
            **/

            virtual bool set(Query* query,unsigned int& colum) const = 0;
    };
};

#endif

/**
 * \class orm::Filter
 * \ingroup backends
 *
 * orm::Filter is a simple class to represent
 * any filter in a query. It can be use as parameter
 * for filter() and exclude() funtions.
 *
 * Usage Exemple:
 * \code
 * orm::Filter(42,"lt",Player::_lvl)
 * \endcode
 *
 * Note : ope is a operator define in Bdd class.
 * \see Bdd::operators
 **/

