#ifndef ORM__OP_HPP
#define ORM_OP_HPP

#include <string>

namespace orm
{
    /**
     * \brief Stor the operator values for filter and ordering
     */
    namespace op
    {
        //filter
        static const std::string exact      = "exact";
        static const std::string iexact     = "iexact";
        static const std::string contains   = "contains" ;
        static const std::string icontains  = "icontains";
        static const std::string regex      = "regex";
        static const std::string iregex     = "iregex";
        static const std::string gt         = "gt";
        static const std::string gte        = "gte";
        static const std::string lt         = "lt";
        static const std::string lte        = "lte";
        static const std::string startswith = "startswith";
        static const std::string endswith   = "endswith";
        static const std::string istartswith= "istartswith";
        static const std::string iendswith  = "iendswith";
        //ordering
        static const char        random     = '?';
        static const char        asc        = '+';
        static const char        desc       = '-';
    }
}
#endif
