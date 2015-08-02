namespace orm
{

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::SqlExtends() : _base_fk(SqlExtends<T,BASE>::ORM_MAKE_NAME(base))
    {
        _base_fk.registerAttr(*static_cast<SqlObject<T>*>(this));
        _base_fk = typename BASE::type_ptr(static_cast<BASE*>(this));
    }

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::~SqlExtends()
    {
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::save(bool recursive,DB& db)
    {
        bool res = BASE::save(recursive,db);
        if(res)
            res = SqlObject<T>::save(recursive,db);
        return res;
    }

    /*SqlExtends::result_type all(DB& db,int max_depth)
    {
        return SqlObject<T>::all(db,max_depth);
    }*/

    /*template <typename T, typename BASE>
    std::ostream& operator<<(std::ostream& output,const SqlExtends<T,BASE>& self)
    {
        return output<<static_cast<SqlObject<T>&>(self);
    }*/

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::loadFromDB(const Query& query,int max_depth)
    {
        return SqlObject<T>::loadFromDB(query,max_depth);
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::loadFromDB(const Query& query,int& prefix,int max_depth)
    {
        return SqlObject<T>::loadFromDB(query,prefix,max_depth);
    }

    /*
    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::save(bool recursive,DB& db)
    {
        //SqlObject<BASE>::save(recursive,db);
        //SqlObject<T>::save(recursive,db);
        return false;
    }
    */

    /*
    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::del(bool recursive, DB& db)
    {
        return false;
    }

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
