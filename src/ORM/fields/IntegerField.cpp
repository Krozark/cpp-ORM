#include <ORM/fields/IntegerField.hpp>

#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    IntegerField::IntegerField(const int& value,const std::string& column) : Attr(value,column)
    {
    }

    IntegerField::IntegerField(const std::string& column) : Attr(0,column)
    {
    }
    
    std::string IntegerField::create(const Bdd& bdd) const
    {
        return bdd.creator().integerField(column,false);
    }
}
