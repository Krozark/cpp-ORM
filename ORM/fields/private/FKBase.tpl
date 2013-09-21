#include <ORM/backends/Query.hpp>

#include <ORM/models/SQLObjectBase.hpp>

namespace orm
{
    /*template<typename T>
    FKBase<T>::FKBase(const int& id,const std::string& colum,bool nullable) : VFK(colum,nullable)
    {
        fk = id;
        value_ptr = T::get(fk);
        loaded = modify = true;
    }*/

    template<typename T>
    FKBase<T>::FKBase(const std::string& colum,bool nullable) : VFK(colum,nullable)/*, value_ptr(0)*/
    {
        //value_ptr.reset(new T());
    }

    template<typename T>
    FKBase<T>::~FKBase()
    {
        /// \todo if cache[T::table] ==1
        //delete value_ptr
        //cache.remove(T::table)
        //value_ptr = 0;
    }


    template<typename T>
    const SQLObjectBase& FKBase<T>::getObject(int max_depth)
    {
        return *getObjectT_ptr(max_depth);
    };

    template<typename T>
    T* FKBase<T>::getObjectT_ptr(int max_depth)
    {
        if (not loaded)
        {
            if(fk>0)
            {
                const unsigned int id = fk;
                value_ptr = T::cache.getOrCreate(id,max_depth);
                loaded = modify = true;
            }
            else
            {
                value_ptr.reset(new T());
                loaded = modify = true;
            }
        }
        return value_ptr.get();
    };

    template<typename T>
    bool FKBase<T>::get(const Query& query,const std::string& prefix,int max_depth)
    {
        const std::string colum_alias(JOIN_ALIAS(prefix,colum));
        bool res = query.get(fk,colum_alias);

        if(res and --max_depth>=0)
        {
            const unsigned int id = fk;
            value_ptr = T::cache.getOrCreate(id,query,colum_alias,max_depth);
            loaded = true;
        }
        /// \todo delete ptr or set to NULL???
        /*else
        {
            value_ptr = NULL;
        }*/
        //res = res and (value_ptr->loadFromBdd(query));
        return res;
    }
    
    template<typename T>
    void FKBase<T>::print(std::ostream& output) const
    {
        if(loaded)
            output<<(*value_ptr);
        else
            output<<"{\"pk\":\""<<fk<<"\",\"_data_\" = null}";
    }

    template<typename T>
    bool FKBase<T>::set(Query& query,const unsigned int& colum)
    {
        /*if (not nullable)
        {
            if(not loaded)
                getObjectT_ptr();
            return query.set(fk,colum);
        }
        return query.setNull(fk,colum);
        */
        if(loaded)
            return query.set(fk,colum);
        return query.setNull(fk,colum);
    };


    /*template<typename T>
    T& FKBase<T>::operator*()
    {
        return getObjectT_ptr();
    };*/

    template<typename T>
    T* FKBase<T>::operator->()
    {
        modify = true;
        return getObjectT_ptr();
    };

    template<typename T>
    FKBase<T>& FKBase<T>::operator=(const FKBase<T>& other)
    {
        modify = true;
        fk = other.fk;
        value_ptr = other.value_ptr;
        loaded = other.loaded;
    }

    template<typename T>
    bool FKBase<T>::save(bool recursive)
    {
        bool res = true;

        if(not nullable)
        {
            getObjectT_ptr();
        }
        if(modify)
        {
            res = value_ptr->save(recursive);
            if(fk<=0)
            {
                value_ptr = T::cache.add(value_ptr);
            }
            fk = value_ptr->pk;
            modify = false;
        }
        return res;
    }

    template<typename T>
    bool FKBase<T>::del(bool recursive)
    {
        bool res = false;
        if(loaded)
        {
            res = value_ptr->del(recursive);
            fk = value_ptr->pk;
        }
        return res;
    }
}
