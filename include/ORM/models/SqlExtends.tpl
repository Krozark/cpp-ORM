namespace orm
{
    template <typename T, typename BASE>
    DB*& SqlExtends<T,BASE>::default_connection = SqlObject<T>::default_connection;

    template <typename T, typename BASE>
    const std::string SqlExtends<T,BASE>::ORM_MAKE_NAME(base_ptr_pk) = "_base_ptr_pk";

    template <typename T, typename BASE>
    const std::string& SqlExtends<T,BASE>::table = SqlObject<T>::table; ///< the table name

    void emptyDeleter(void* obj)
    {
    }

    static int counter = 0;

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::SqlExtends() : _base_fk(SqlExtends<T,BASE>::ORM_MAKE_NAME(base_ptr_pk))
    {
        _base_fk.registerAttr(*static_cast<SqlObject<T>*>(this));

        _base_fk = typename BASE::type_ptr(static_cast<BASE*>(this),emptyDeleter); //avoid to delete this twice

        _save_nb = 0;
    }

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::~SqlExtends()
    {
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::save(bool recursive,DB& db)
    {
        bool res = false;
        if(_save_nb == 0) // hack to avoid recursion due to extends
        {
            ++_save_nb;
            res = SqlObject<BASE>::save(recursive,db);
            res |= SqlObject<T>::save(recursive,db);
        }
        --_save_nb;
        return res;
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::del(bool recursive, DB& db)
    {
        std::cout<<"SqlExtends<T>::del()"<<std::endl;
        bool res = false;
        res = SqlObject<BASE>::del(recursive,db);
        res |= SqlObject<T>::del(recursive,db);
        return res;
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::loadFromDB(const Query& query,int& prefix,int max_depth)
    {
        return SqlObject<T>::loadFromDB(query,prefix,max_depth);
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
        return table;
    }
    */
}
