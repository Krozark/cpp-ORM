namespace orm
{

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::SqlExtends()
    {
        //_base_fk.registerAttr(*this);
    }

    template <typename T, typename BASE>
    SqlExtends<T,BASE>::~SqlExtends()
    {
    }

    template <typename T, typename BASE>
    bool SqlExtends<T,BASE>::save(bool recursive,DB& db)
    {
        //SqlObject<BASE>::save(recursive,db);
        //SqlObject<T>::save(recursive,db);
        return false;
    }

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
