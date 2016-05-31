
namespace orm
{
    class SlqObjectBase;

    template<typename T>
    Register<T>::Register()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_REDMAGENTA<<"[Register] Table "<<SqlObject<T>::table<<ORM_COLOUR_REDNONE<<std::endl;
        #endif

        static typename T::pointer tmp = T::create();
        for(VAttr* attr: static_cast<SqlObject<T>*>(tmp.get())->attrs)
        {
            #if ORM_DEBUG & ORM_DEBUG_REGISTER
            //std::cerr<<ORM_COLOUR_REDMAGENTA<<"[Register] Attr "<<attr->column<<ORM_COLOUR_REDNONE<<std::endl;
            #endif
            SqlObject<T>::column_attrs.emplace_back(attr);
        }
        for(VFK* fk: static_cast<SqlObject<T>*>(tmp.get())->fks)
        {
            #if ORM_DEBUG & ORM_DEBUG_REGISTER
            //std::cerr<<ORM_COLOUR_REDMAGENTA<<"[Register] Fk "<<fk->column<<ORM_COLOUR_REDNONE<<std::endl;
            #endif
            SqlObject<T>::column_fks.emplace_back(fk);
        }

        Tables::getFactory().add(SqlObject<T>::table, [](){
            return std::dynamic_pointer_cast<SqlObjectBase>(T::create());
        });

        Tables::_create.push_back(
                                 []()->bool{
                                    return SqlObject<T>::createTable();
                                 }
                                );

        Tables::_drop.push_back(
                               []()->bool{
                                return SqlObject<T>::dropTable();
                                }
                            );

        Tables::_clear.push_back(
                                   []()->bool{
                                    return SqlObject<T>::clearTable();
                                    }
                                );

        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_REDMAGENTA<<"[Register] END Table "<<SqlObject<T>::table<<ORM_COLOUR_REDNONE<<std::endl;
        #endif
    }
}
