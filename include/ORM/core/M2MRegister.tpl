namespace orm
{

    template<typename OWNER,typename RELATED>
    M2MRegister<OWNER,RELATED>::M2MRegister()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_REDMAGENTA<<"[M2MRegister] Table "<<ManyToMany<OWNER,RELATED>::table<<ORM_COLOUR_REDNONE<<std::endl;
        #endif

        Tables::_create.push_back(
                                 []()->bool{
                                    return ManyToMany<OWNER,RELATED>::create();
                                 }
                                );

        Tables::_drop.push_back(
                               []()->bool{
                                return ManyToMany<OWNER,RELATED>::drop();
                                }
                            );

        Tables::_clear.push_back(
                                   []()->bool{
                                    return ManyToMany<OWNER,RELATED>::clear();
                                    }
                                );

        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_REDMAGENTA<<"[M2MRegister] END Table "<<ManyToMany<OWNER,RELATED>::table<<ORM_COLOUR_REDNONE<<std::endl;
        #endif
    }
}
