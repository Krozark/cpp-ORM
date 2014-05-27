#ifndef ORM_FILTERSET_HPP
#define ORM_FILTERSET_HPP

//#include <ORM/backends/private/VFilter.hpp>
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    class FilterSet
    {
        public:
            template<typename T>
            FilterSet(const Filter<T>& f);
            FilterSet(const std::string& op,const FilterSet* f);
            FilterSet(const FilterSet* left,const std::string& op,const FilterSet* right);

            virtual ~FilterSet();


            FilterSet(const FilterSet&) = delete;
            FilterSet& operator=(const FilterSet&) = delete;

            FilterSet(FilterSet&&) = default;
            FilterSet& operator=(FilterSet&&) = default;

            void __print__() const;

        private:
            const FilterSet* left;
            const std::string op;
            const FilterSet* right;


            enum Type {
                LEAF,
                UNARY,
                BINARY,
            } const type;
            
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

    FilterSet operator!(const FilterSet& a);

    FilterSet operator&&(const FilterSet& a, const FilterSet& b);
    FilterSet operator||(const FilterSet& a,const FilterSet& b);

    FilterSet operator&&(FilterSet&& a, FilterSet&& b);
    FilterSet operator||(FilterSet&& a, FilterSet&& b);
}
#include <ORM/backends/private/FilterSet.tpl>
#endif
