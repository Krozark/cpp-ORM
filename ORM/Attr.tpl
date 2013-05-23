#include "Query.hpp"

namespace orm 
{
    template<typename T>
    Attr<T>::Attr(const T& val,const std::string col) : VAttr(col), value(val)
    {
    };

    template<typename T>
    bool get(const Query& query)
    {
        return query.get(value,colum);
    };

    template<typename T>
    void print(std::ostream& output) const
    {
        output<<value;
    };


};
