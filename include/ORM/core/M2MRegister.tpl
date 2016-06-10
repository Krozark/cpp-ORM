namespace orm
{

    template<typename OWNER,typename RELATED>
    M2MRegister<OWNER,RELATED>::M2MRegister()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_MAGENTA<<"[M2MRegister] Table "<<ManyToMany<OWNER,RELATED>::_table<<ORM_COLOUR_NONE<<std::endl;
        #endif

        Tables::_create.push_back(
                                 []()->bool{
                                    return ManyToMany<OWNER,RELATED>::createTable();
                                 }
                                );

        Tables::_drop.push_back(
                               []()->bool{
                                return ManyToMany<OWNER,RELATED>::dropTable();
                                }
                            );

        Tables::_clear.push_back(
                                   []()->bool{
                                    return ManyToMany<OWNER,RELATED>::clearTable();
                                    }
                                );

        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_MAGENTA<<"[M2MRegister] END Table "<<ManyToMany<OWNER,RELATED>::_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
    }
}
