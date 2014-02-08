#include <ORM/fields/AutoField.hpp>

#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    AutoField::AutoField(const int& value,const std::string& column) : Attr(value,column)
    {
    }
    
    std::string AutoField::create(const Bdd& bdd) const
    {
        return bdd.creator().autoField(column);
    }
}
