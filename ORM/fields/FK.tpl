#include <ORM/backends/Query.hpp>

#include <ORM/models/SQLObjectBase.hpp>

namespace orm
{
    template<typename T>
    FK<T>::FK(const int& id,const std::string& colum) : VFK(colum)
    {
        fk = id;
        value_ptr = T::get(fk);
    }

    template<typename T>
    FK<T>::FK(const std::string& colum) : VFK(colum), value_ptr(0)
    {
        value_ptr = new T();
    }

    template<typename T>
    FK<T>::~FK()
    {
       if(value_ptr and fk == -1)
        {
            delete value_ptr;
        }
        //TODO if cache[T::table] ==1
        //delete value_ptr
        //cache.remove(T::table)
        value_ptr = 0;
    }


    template<typename T>
    const SQLObjectBase& FK<T>::getObject()const
    {
        return *value_ptr;
    }

    template<typename T>
    bool FK<T>::get(const Query& query)
    {
        bool res = query.get(fk,colum);
        //TODO cheque cache
        res = res and (value_ptr->loadFromBdd(query));
        //TODO add to cache??
        return res;
    }
    
    template<typename T>
    void FK<T>::print(std::ostream& output) const
    {
        output<<"{"<<(*value_ptr)<<"}";
    }

    template<typename T>
    bool FK<T>::set(Query& query,const unsigned int& colum)const
    {
        return query.set(fk,colum);
    };

    template<typename T>
    FK<T>& FK<T>::operator=(const FK<T>& other)
    {
        modify = true;
        fk = other.fk;
        if(value_ptr and fk == -1)
        {
            delete value_ptr;
        }
        //TODO --on cache counter
        value_ptr = other.value_ptr;
        //TODO ++ on cache counter
    }

    template<typename T>
    bool FK<T>::save(bool recursive,bool force)
    {
        bool res = value_ptr->save(recursive,force);
        fk = value_ptr->pk;
        return res;
    }

}
