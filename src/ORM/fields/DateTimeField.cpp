#include <ORM/fields/DateTimeField.hpp>

#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    DateTimeField::DateTimeField(const std::string& value,const std::string& column) : Attr(value,column)
    {
    }

    DateTimeField::DateTimeField(const std::string& column) : Attr("0000-00-00 00:00:00",column)
    {
    }

    DateTimeField DateTimeField::now()
    {
        return DateTimeField(0);
    }
    
    std::string DateTimeField::create(const Bdd& bdd) const
    {
        return bdd.creator().dateTimeField(column,false);
    }
}
