#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <string>
/**
 * \brief A class representing filter in query
 **/
namespace orm
{
    template<typename T> class SQLObject;
    template<typename T> class QuerySet;

    class Filter
    {
        public:
            /**
             * \brief Create a filter
             *
             * \param colum Colum where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            template<typename T>
            Filter(const std::string& colum,const std::string& ope, const T& value);
            
            /**
             * \brief Print the content of the filter for debug help
             **/
            void __print__() const;

        private:
            template<typename T> friend class SQLObject;
            template<typename T> friend class QuerySet;

            const std::string colum;
            const std::string ope;
            const std::string value;
    };
};

#include <ORM/backends/Filter.tpl>
#endif

/**
 * \class Filter
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
 * \see Bdd
 **/

