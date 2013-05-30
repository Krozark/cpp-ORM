#include "Filter.hpp"

namespace orm
{
    Filter::Filter(const std::string& col,const std::string& op, const std::string& val) : colum(col), ope(op), value(val)
    {
    }
};
