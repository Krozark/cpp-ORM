#include <ORM/fields/FloatField.hpp>

#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    FloatField::FloatField(const float& value,const std::string& column) : Attr(value,column)
    {
    }

    FloatField::FloatField(const std::string& column) : Attr(0,column)
    {
    }
    
    std::string FloatField::create(const Bdd& bdd) const
    {
        return bdd.creator().floatField(column,false);
    }
}
