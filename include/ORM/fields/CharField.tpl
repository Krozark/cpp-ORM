
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
    std::string CharField<max_length>::create(const Bdd& bdd) const
    {
        return bdd.creator().charField(column,max_length,false);
    }
}
