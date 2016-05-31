
namespace orm
{

    template<size_t max_length>
    CharField<max_length>::CharField(const std::string& value,const std::string& column) : Attr(value,column)
    {
    }

    template<size_t max_length>
    CharField<max_length>::CharField(const std::string& column) : Attr("",column)
    {
    }

    template<size_t max_length>
    std::string CharField<max_length>::_create(const DB& db) const
    {
        return db.creator().charField(_column,max_length,false);
    }
}
