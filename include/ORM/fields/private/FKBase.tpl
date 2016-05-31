#include <ORM/backends/DB.hpp>
#include <ORM/backends/Query.hpp>
#include <ORM/models/SqlObjectBase.hpp>

namespace orm
{
    /*template<typename T>
    FKBase<T>::FKBase(const int& id,const std::string& column,bool nullable) : VFK(column,nullable)
    {
        fk = id;
        value_ptr = T::get(fk);
        loaded = modify = true;
    }*/
    template<typename T>
    FKBase<T>::~FKBase()
    {
        /// \todo if cache[T::table] ==1
        //delete value_ptr
        //cache.remove(T::table)
        //value_ptr = 0;
    }

    template<typename T>
    bool FKBase<T>::save(bool recursive,DB& db)
    {
        bool res = false;

        if(not nullable)
        {
            setObjectT_ptr(db);
        }


        if(_modified)
        {
            _modified = false; //avoid loop cause by user callbacks
            res = value_ptr->save(recursive,db);
            if(fk<=0)
            {
                value_ptr = T::cache._add(value_ptr);
            }
            _modified = value_ptr->pk != fk;
            fk = value_ptr->pk;
        }
        return res;
    }

    template<typename T>
    bool FKBase<T>::del(bool recursive,DB& db)
    {
        bool res = false;
        //if(loaded)
        if(value_ptr.get() and value_ptr->pk != -1)
        {
            res = value_ptr->del(recursive,db);
            fk = value_ptr->pk;
        }
        return res;
    }

    template<typename T>
    typename T::pointer FKBase<T>::operator->()
    {
        _modified = true;
        setObjectT_ptr(*T::default_connection);
        return value_ptr;
    };

    template<typename T>
    T& FKBase<T>::operator*()
    {
        setObjectT_ptr(*T::default_connection);
        return *value_ptr;
    };

    template<typename T>
    FKBase<T>::operator typename T::pointer() const
    {
        return value_ptr;
    }

    template<typename T>
    FKBase<T>::operator bool()const
    {
        return value_ptr.get();
    }

    template<typename T>
    FKBase<T>& FKBase<T>::operator=(const FKBase<T>& other)
    {
        _modified = true;
        fk = other.fk;
        value_ptr = other.value_ptr;
        //loaded = other.loaded;
        return *this;
    }

    template<typename T>
    FKBase<T>& FKBase<T>::operator=(const typename Cache<T>::pointer& other)
    {
        _modified = true;
        fk = other->pk;
        value_ptr = other;
        //loaded = true;
        return *this;
    }


    template<typename T>
    std::ostream& FKBase<T>::printValue(std::ostream& output)const
    {
        //if(loaded)
        if(value_ptr.get())
            output<<(*value_ptr);
        else
            output<<"{\""<<T::ORM_MAKE_NAME(pk)<<"\":\""<<fk<<"\",\"_data_\" = null}";
        return output;
    }

    template<typename T>
    bool FKBase<T>::test()const
    {
        return value_ptr.get();
    }

    template<typename T>
    DB& FKBase<T>::getDefaultDataBase()const
    {
        return *T::default_connection;
    }

    template<typename T>
    bool FKBase<T>::setValue(SqlObjectBase::pointer& ptr)
    {
        typename Cache<T>::pointer other = std::dynamic_pointer_cast<T>(ptr);
        if (other)
        {
            (*this) = other;
            return true;
        }
        return false;
    }

    template<typename T>
    const std::string& FKBase<T>::getTable() const
    {
        return T::table;
    }

    /////////////////////// PROTECTED /////////////////////////

    template<typename T>
    FKBase<T>::FKBase(const std::string& column,bool nullable) : VFK(column,nullable)/*, value_ptr(0)*/
    {
    }


    template<typename T>
    bool FKBase<T>::_setToQuery(Query& query,const unsigned int& column)
    {
        if(value_ptr.get())
        {
            if(fk<=0)
            {
                fk = value_ptr->pk;
            }
            if(fk>0)
            {
                return query._set(fk,column);
            }
        }
        return query._setNull(fk,column);
    };

    template<typename T>
    bool FKBase<T>::_getFromQuery(const Query& query,int& prefix,int max_depth)
    {
        bool res = query._getPk(fk,prefix);

        if(--max_depth>=0)
        {
            if(res)
            {
                const unsigned int id = fk;
                if(test())
                {
                    value_ptr->T::loadFromDB(query,prefix,max_depth);

                    if(T::cache._add(value_ptr) != value_ptr)
                    {
                        std::cerr<<ORM_COLOUR_RED<<"[FKBase<T>::get] imposible to insert new value to cahe. Undefine behaviours when querying table "<<typeid(T).name()<<ORM_COLOUR_NONE<<std::endl;
                    }
                }
                else
                {
                    value_ptr = T::cache.getOrCreate(id,query,prefix,max_depth);
                }
                //loaded = true;
            }
            else
            {
                T::incDepth(prefix,max_depth);
                if(nullable)
                    res = true;
            }
        }
        else if(nullable)
            res = true;

        return res;
    }

    template<typename T>
    void FKBase<T>::setObjectT_ptr(DB& db,int max_depth)
    {
        //if (not loaded)
        if (not value_ptr.get())
        {
            if(fk>0)
            {
                const unsigned int id = fk;
                value_ptr = T::cache.getOrCreate(id,db,max_depth);
                /*loaded =*/ _modified = true;
            }
            else
            {
                value_ptr = T::create();
                /*loaded =*/ _modified = true;
            }
        }
    };



    template<typename T>
    std::string FKBase<T>::_makeName(DB& db, const std::string& prefix,int max_depth) const
    {
        std::string q_str(",\n "+db._escapeColumn(prefix)+"."+db._escapeColumn(_column)+" AS "+JOIN_ALIAS(prefix,_column));

        if(--max_depth <0)
        {
            return q_str;
        }

        const std::string table_alias = MAKE_PREFIX(prefix,_column);

        q_str+=",";
        T::nameAttrs(q_str,table_alias,max_depth,db);
        return q_str;
    }

    template<typename T>
    void FKBase<T>::incDepth(int& depth,int max_depth) const
    {
        if(--max_depth>=0)
        {
            T::incDepth(depth,max_depth);
        }
    }


    template<typename T>
    const SqlObjectBase& FKBase<T>::getObject(DB& db,int max_depth)
    {
        setObjectT_ptr(db,max_depth);
        return *value_ptr;
    };

    template<typename T>
    std::string FKBase<T>::_create(const DB& db) const
    {
        return db.creator().fk(_column,T::table,nullable);
    }
}
