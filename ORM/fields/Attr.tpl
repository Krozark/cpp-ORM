#include <ORM/backends/Query.hpp>

namespace orm 
{
    template<typename T>
    Attr<T>::Attr(const T& val,const std::string& col) : VAttr(col), value(val)
    {
    };

    template<typename T>
    Attr<T>::Attr(const std::string& col) : VAttr(col) , value()
    {
    };

    template<typename T>
    bool Attr<T>::get(const Query& query)
    {
        return query.get(value,colum);
    };

    template<typename T>
    void Attr<T>::print(std::ostream& output) const
    {
        output<<value;
    };

    template<typename T>
    bool Attr<T>::set(Query& query,const unsigned int& colum)const
    {
        return query.set(value,colum);
    };
};
