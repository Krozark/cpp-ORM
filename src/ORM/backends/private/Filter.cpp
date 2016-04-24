#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    //special date type
    template<>
    tm filter_value_helper_2<tm>(const tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(tm));
        ::mktime(&tmp);
        tmp.tm_year +=1900;
        tmp.tm_mon +=1;
        tmp.tm_isdst = -1;
        return tmp;
    };

    //special date type
    template<>
    tm filter_clone_helper_2<tm>(const tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(tm));
        tmp.tm_year -=1900;
        tmp.tm_mon -=1;
        tmp.tm_isdst = -1;
        return tmp;
    };
}
