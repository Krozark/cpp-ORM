#include <ORM/fields/DateTimeField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    DateTimeField::DateTimeField(const std::string& value,const std::string& column) : Attr(value,column)
    {
    }

    DateTimeField::DateTimeField(const std::string& column) : Attr("0000-00-00 00:00:00",column)
    {
    }

    /*DateTimeField DateTimeField::now()
    {
        //\todo TODO
        return DateTimeField("",column);
    }*/
    
    std::string DateTimeField::create(const DB& db) const
    {
        return db.creator().dateTimeField(column,false);
    }
}
