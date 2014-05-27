#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <ORM/backends/private/VFilter.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{
    /**
     * \brief A class to build filters
     * T have to be a primitiv type (char, bool,int, float, double, unsigned, long, long long)
     **/
    template<typename T>
    class Filter : public VFilter
    {
        public:
            /**
             * \brief Create a filter
             *
             * \param column column where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            Filter(const std::string& column,const std::string& ope,const T& value);

            /**
             * \brief Create a filter
             *
             * \param column column where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            Filter(std::string&& column,const std::string& ope,const T& value);

            virtual ~Filter();

            /**
             * \brief Print the content of the filter for debug help
             **/
            virtual void __print__() const final;

        protected:
            const std::string column; ///< Colum to apply filter
            const std::string ope; ///< operator to use. \see Bdd::operators
            const T value; ///< Store the value of the filter to compare with

           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param column column index
            *
            * \return false if fail
            **/
            virtual bool set(Query* query,unsigned int& column) const final;

            /**
             * \brief add the sql code to the query
             * \param query sql to append to
             * \param bdd data base to use
             */
            virtual void toQuery(std::string& query,Bdd& bdd) const final;
    };
}
#include <ORM/backends/private/Filter.tpl>
#endif
