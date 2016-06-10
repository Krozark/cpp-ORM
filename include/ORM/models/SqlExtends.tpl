namespace orm
{
    template <typename T, typename BASE>
    const std::string SqlExtends<T,BASE>::ORM_MAKE_NAME(base_obj_ptr) = "_base_obj_ptr";

    template <typename T, typename BASE>
    const std::string& SqlExtends<T,BASE>::_table = SqlObject<T>::_table; ///< the table name

    template <typename T, typename BASE>
    Cache<T>& SqlExtends<T,BASE>::_cache = SqlObject<T>::_cache;

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::SqlExtends() : _baseFk(SqlExtends<T,BASE>::ORM_MAKE_NAME(base_obj_ptr))
    {
        _baseFk.registerAttr(*static_cast<SqlObject<T>*>(this));

        _baseFk = typename BASE::pointer(static_cast<BASE*>(this), [](void* obj){}); //avoid to delete this twice

        _saveNb = 0;
    }

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::~SqlExtends()
    {
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::save(bool recursive,DB& db)
    {
        bool res = false;
        if(_saveNb == 0) // hack to avoid recursion due to extends
        {
            ++_saveNb;
            res = SqlObject<BASE>::save(recursive,db);
            res |= SqlObject<T>::save(recursive,db);
        }
        --_saveNb;
        return res;
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::del(bool recursive, DB& db)
    {
        bool res = false;
        res = SqlObject<BASE>::del(recursive,db);
        res |= SqlObject<T>::del(recursive,db);
        return res;
    }

    template <typename T, typename BASE>
    DB& SqlExtends<T,BASE>::staticGetDefaultDataBase()
    {
        return SqlObject<T>::staticGetDefaultDataBase();
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::_loadFromDB(const Query& query,int& prefix,int max_depth)
    {
        return SqlObject<T>::_loadFromDB(query,prefix,max_depth);
    }

    /*

    template <typename T, typename BASE>
    void SqlExtends<T,BASE>::_nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
    }

    template <typename T, typename BASE>
    void SqlExtends<T,BASE>::_nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
    }

    template <typename T, typename BASE>
    void SqlExtends<T,BASE>::_makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
    }

    template <typename T, typename BASE>
    const std::string& SqlExtends<T,BASE>::getTable() const
    {
        return _table;
    }
    */
}
