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
        //TODO if cash[T::table] ==1
        //delete value_ptr
        //cash.remove(T::table)
        value_ptr = 0;
    }


    template<typename T>
    bool FK<T>::get(const Query& query)
    {
        int id;
        bool res = query.get(id,colum);
        return res and (value_ptr = T::get(id));
    }
    
    template<typename T>
    void FK<T>::print(std::ostream& output) const
    {
        output<<(*value_ptr);
    }

    template<typename T>
    bool FK<T>::set(Query& query,const unsigned int& colum)const
    {
        return query.set(value_ptr->pk,colum);
    };

    template<typename T>
    FK<T>& FK<T>::operator=(const FK<T>& other)
    {
        //TODO --on cash counter
        value_ptr = other.value_ptr;
        //TODO ++ on cash counter
    }

}
