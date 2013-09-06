#ifndef ORM_EXTERNALS_HPP
#define ORM_EXTERNALS_HPP

#include <ORM/debug.hpp>

namespace orm
{
    static const std::string TABLE_ALIAS_SEPARATOR("__");

    static inline const std::string JOIN_ALIAS(const std::string& prefix,const std::string& colum)
    {
        return prefix+TABLE_ALIAS_SEPARATOR+colum;
    };

    static inline const std::string MAKE_PREFIX(const std::string& prefix,const std::string& table)
    {
        return (prefix.size()>0)?JOIN_ALIAS(prefix,table):table;
    };
}
#endif