namespace std
{
    const string& to_string(const std::string& p)  {return p;}
}

namespace orm
{
    template<typename T>
    Filter::Filter(const std::string& col,const std::string& op, const T& val) : colum(col), ope(op), value(std::to_string(val))
    {
    }

    template<>
    Filter::Filter(const std::string& col,const std::string& op, const std::string& val) : colum(col), ope(op), value(val)
    {
    }

    template<>
    Filter::Filter(const std::string& col,const std::string& op,char* const& val) : colum(col), ope(op), value(std::string(val))
    {
    }
};
