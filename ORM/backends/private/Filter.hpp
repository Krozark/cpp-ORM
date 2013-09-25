#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <ORM/backends/private/VFilter.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{
    class Query;

    template<typename T>
    class Filter : public VFilter
    {
        public:
            /**
             * \brief Create a filter
             *
             * \param colum Colum where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            Filter(const std::string& colum,const std::string& ope,const T& value);

            /**
             * \brief Create a filter
             *
             * \param colum Colum where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            Filter(std::string&& colum,const std::string& ope,const T& value);

            /**
             * \brief Print the content of the filter for debug help
             **/
            virtual void __print__() const;
            

        protected:
            const T value;
           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param colum Colum index
            *
            * \return false if fail
            **/
            virtual bool set(Query* query,unsigned int& colum) const;
    };
}
#include <ORM/backends/private/Filter.tpl>
#endif
