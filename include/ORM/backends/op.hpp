#ifndef ORM_OP_HPP
#define ORM_OP_HPP

#include <string>

namespace orm
{
    /**
     * \brief Stor the operator values for filter and ordering
     */
    namespace op
    {
        //filters
        static const  char exact[] = "exact";
        static const  char iexact[] = "iexact";
        static const  char contains[] = "contains";
        static const  char icontains[] = "icontains";
        static const  char regex[] = "regex";
        static const  char iregex[] = "iregex";
        static const  char gt[] = "gt";
        static const  char gte[] = "gte";
        static const  char lt[] = "lt";
        static const  char lte[] = "lte";
        static const  char startswith[] = "startswith";
        static const  char endswith[] = "endswith";
        static const  char istartswith[] = "istartswith";
        static const  char iendswith[] = "iendswith";
        //ordering
        static const  char random = '?';
        static const  char asc = '+';
        static const  char desc = '-';
    };

}
#endif
