#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template<>
    bool Filter<std::string>::set(Query* query,unsigned int& column) const
    {
        std::string v(query->bdd.formatValue(ope,value));
        return query->set(v,column);
    }
}
