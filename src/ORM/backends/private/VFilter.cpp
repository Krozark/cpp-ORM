#include <ORM/backends/private/VFilter.hpp>

namespace orm
{
    VFilter::VFilter(const std::string& col,const std::string& op) : column(col), ope(op)
    {
    }

    VFilter::VFilter(std::string&& col,const std::string& op) : column(col), ope(op)
    {
    }

    VFilter::~VFilter()
    {
    }
};
