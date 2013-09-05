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
    FK<T>::FK(const std::string& colum) : VFK(colum)/*, value_ptr(0)*/
    {
        //value_ptr.reset(new T());
    }

    template<typename T>
    FK<T>::~FK()
    {
        //TODO if cache[T::table] ==1
        //delete value_ptr
        //cache.remove(T::table)
        //value_ptr = 0;
    }


    template<typename T>
    const SQLObjectBase& FK<T>::getObject()
    {
        if (value_ptr == NULL)
            value_ptr.reset(new T());
        return *value_ptr;
    }

    //TODO getOrCreate max_depth
    template<typename T>
    bool FK<T>::get(const Query& query,const std::string& prefix,int max_depth)
    {
        const std::string colum_alias(JOIN_ALIAS(prefix,colum));
        bool res = query.get(fk,colum_alias);

        if(res and --max_depth>=0)
        {
            const unsigned int id = fk;
            value_ptr = T::cache.getOrCreate(id,query,colum_alias,max_depth);
        }
        //TODO delete ptr or set to NULL???
        /*else
        {
            value_ptr = NULL;
        }*/
        //res = res and (value_ptr->loadFromBdd(query));
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
        value_ptr = other.value_ptr;
    }

    template<typename T>
    bool FK<T>::save(bool recursive,bool force)
    {
        bool res = value_ptr->save(recursive,force);
        fk = value_ptr->pk;
        return res;
    }

}
