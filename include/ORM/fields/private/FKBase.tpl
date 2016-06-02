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
        /// \todo if _cache[T::_table] ==1
        //delete value_ptr
        //_cache.remove(T::_table)
        //value_ptr = 0;
    }

    template<typename T>
    bool FKBase<T>::save(bool recursive,DB& db)
    {
        bool res = false;

        if(not _nullable)
        {
            _setObjectT_ptr(db);
        }


        if(_modified)
        {
            _modified = false; //avoid loop cause by user callbacks
            res = _valuePtr->save(recursive,db);
            if(_fk<=0)
            {
                _valuePtr = T::_cache._add(_valuePtr);
            }
            _modified = true;
            _fk = _valuePtr->pk;
        }
        return res;
    }

    template<typename T>
    bool FKBase<T>::del(bool recursive,DB& db)
    {
        bool res = false;
        //if(loaded)
        if(_valuePtr.get() and _valuePtr->pk != -1)
        {
            res = _valuePtr->del(recursive,db);
            _fk = _valuePtr->pk;
        }
        return res;
    }

    template<typename T>
    typename T::pointer FKBase<T>::operator->()
    {
        _modified = true;
        _setObjectT_ptr(*T::defaultDBConnection);
        return _valuePtr;
    };

    template<typename T>
    T& FKBase<T>::operator*()
    {
        _setObjectT_ptr(*T::defaultDBConnection);
        return *_valuePtr;
    };

    template<typename T>
    FKBase<T>::operator typename T::pointer() const
    {
        return _valuePtr;
    }

    template<typename T>
    FKBase<T>::operator bool()const
    {
        return _valuePtr.get();
    }

    template<typename T>
    FKBase<T>& FKBase<T>::operator=(const FKBase<T>& other)
    {
        _modified = true;
        _fk = other._fk;
        _valuePtr = other._valuePtr;
        //loaded = other.loaded;
        return *this;
    }

    template<typename T>
    FKBase<T>& FKBase<T>::operator=(const typename Cache<T>::pointer& other)
    {
        _modified = true;
        _fk = other->pk;
        _valuePtr = other;
        //loaded = true;
        return *this;
    }


    template<typename T>
    std::ostream& FKBase<T>::printValue(std::ostream& output)const
    {
        //if(loaded)
        if(_valuePtr)
        {
            output<<(*_valuePtr);
        }
        else
        {
            output<<"{\""<<T::ORM_MAKE_NAME(pk)<<"\":\""<<_fk<<"\",\"_data_\" = null}";
        }
        return output;
    }

    template<typename T>
    bool FKBase<T>::test()const
    {
        return (_valuePtr != nullptr);
    }

    template<typename T>
    DB& FKBase<T>::getDefaultDataBase()const
    {
        return *T::defaultDBConnection;
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
        return T::_table;
    }

    /////////////////////// PROTECTED /////////////////////////

    template<typename T>
    FKBase<T>::FKBase(const std::string& column,bool nullable) : VFK(column,nullable)/*, value_ptr(0)*/
    {
    }


    template<typename T>
    bool FKBase<T>::_setToQuery(Query& query,const unsigned int& column)
    {
        if(_valuePtr)
        {
            if(_fk<=0)
            {
                _fk = _valuePtr->pk;
            }
            if(_fk>0)
            {
                return query._set(_fk,column);
            }
        }
        return query._setNull(_fk,column);
    };

    template<typename T>
    bool FKBase<T>::_getFromQuery(const Query& query,int& prefix,int max_depth)
    {
        bool res = query._getPk(_fk,prefix);

        if(--max_depth>=0)
        {
            if(res)
            {
                const unsigned int id = _fk;
                if(test())
                {
                    _valuePtr->T::_loadFromDB(query,prefix,max_depth);

                    if(T::_cache._add(_valuePtr) != _valuePtr)
                    {
                        std::cerr<<ORM_COLOUR_RED<<"[FKBase<T>::get] imposible to insert new value to cahe. Undefine behaviours when querying table "<<typeid(T).name()<<ORM_COLOUR_NONE<<std::endl;
                    }
                }
                else
                {
                    _valuePtr = T::_cache.getOrCreate(id,query,prefix,max_depth);
                }
                //loaded = true;
            }
            else
            {
                T::_incDepth(prefix,max_depth);
                if(_nullable)
                {
                    res = true;
                }
            }
        }
        else if(_nullable)
        {
            res = true;
        }

        return res;
    }

    template<typename T>
    void FKBase<T>::_setObjectT_ptr(DB& db,int max_depth)
    {
        //if (not loaded)
        if (_valuePtr == nullptr)
        {
            if(_fk>0)
            {
                const unsigned int id = _fk;
                _valuePtr = T::_cache.getOrCreate(id,db,max_depth);
                /*loaded =*/ _modified = true;
            }
            else
            {
                _valuePtr = T::create();
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
        T::_staticNameAttrs(q_str,table_alias,max_depth,db);
        return q_str;
    }

    template<typename T>
    void FKBase<T>::_incDepth(int& depth,int max_depth) const
    {
        if(--max_depth>=0)
        {
            T::_incDepth(depth,max_depth);
        }
    }


    template<typename T>
    const SqlObjectBase& FKBase<T>::_getObject(DB& db,int max_depth)
    {
        _setObjectT_ptr(db,max_depth);
        return *_valuePtr;
    };

    template<typename T>
    std::string FKBase<T>::_create(const DB& db) const
    {
        return db.creator().fk(_column,T::_table,_nullable);
    }
}
