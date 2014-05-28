#ifndef ORM_FILTERSET_HPP
#define ORM_FILTERSET_HPP

//#include <ORM/backends/private/VFilter.hpp>
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    class FilterSet
    {
        public:

            FilterSet(FilterSet&& a);
            FilterSet(const FilterSet& a);

            template<typename RELATED,typename T>
            FilterSet(Filter<RELATED,T>&& f);

            FilterSet(FilterSet&& l, const std::string& o);
            FilterSet(const FilterSet& l, const std::string& o);

            FilterSet(FilterSet&& l, const std::string o,FilterSet&& r);

            ~FilterSet();

            void __print__(const Bdd& bdd)const;


        private:
            void* left;
            std::string ope;
            FilterSet* right;


            enum Type {
                LEAF,
                UNARY,
                BINARY,
            } type;
            
        protected:
            template<typename T> friend class QuerySet;
           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param column column index
            *
            * \return false if fail
            **/
            bool set(Query* query,unsigned int& column) const;

            /**
             * \brief add the sql code to the query
             * \param query sql to append to
             * \param bdd data base to use
             */
            void toQuery(std::string& query,Bdd& bdd) const;
    };

    FilterSet operator!(FilterSet&& a);
    FilterSet operator!(const FilterSet& a);

    FilterSet operator&&(FilterSet&& a, FilterSet&& b);
    FilterSet operator||(FilterSet&& a, FilterSet&& b);
}
#include <ORM/backends/private/FilterSet.tpl>
#endif
