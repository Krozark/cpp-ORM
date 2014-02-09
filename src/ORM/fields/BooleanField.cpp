#include <ORM/fields/BooleanField.hpp>

#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    BooleanField::BooleanField(const bool& value,const std::string& column) : Attr(value,column)
    {
    }
    
    std::string BooleanField::create(const Bdd& bdd) const
    {
        return bdd.creator().booleanField(column,false);
    }
}
