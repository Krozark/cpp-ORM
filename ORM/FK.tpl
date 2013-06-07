#include "Query.hpp"

namespace orm
{
    template<typename T>
    FK<T>::FK(const int& id,const std::string& colum) : VAttr(colum), value_ptr(0)
    {
    }

    template<typename T>
    FK<T>::FK(const std::string& colum) : VAttr(colum), value_ptr(0)
    {
    }

    template<typename T>
    FK<T>::~FK()
    {
    }


    template<typename T>
    bool FK<T>::get(const Query& query)
    {
        return query.get(value,colum);
    }
    
    template<typename T>
    void FK<T>::print(std::ostream& output) const
    {
        output<<value;
    }

    template<typename T>
    bool FK<T>::set(Query& query,const unsigned int& colum)const
    {
        return query.set(value,colum);
    };

}
