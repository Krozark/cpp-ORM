#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/private/QuerySet.hpp>


namespace orm
{
    template<typename T>
    SQLObject<T>::SQLObject()
    {
    };

    template<typename T>
    T* SQLObject<T>::createFromBdd(const Query& query,int& prefix, int max_depth)
    {
        T* res = new T();
        if(not res->loadFromBdd(query,prefix,max_depth))
        {
            delete res;
            res = 0;
        }
        return res;
    };

    template<typename T>
    typename Cache<T>::type_ptr& SQLObject<T>::get(const unsigned int& id,Bdd& bdd,int max_depth)
    {
        return cache.getOrCreate(id,bdd,max_depth);
    }
    
    template<typename T>
    T* SQLObject<T>::_get_ptr(const unsigned int id,Bdd& bdd,int max_depth)
    {
        if(max_depth <0)
            return 0;

        std::string q_str ="SELECT ";
        nameAttrs(q_str,table,max_depth,bdd);
                                    
        q_str+="\nFROM ";
        nameTables(q_str,"",max_depth,bdd);

        q_str+=" \nWHERE ("
        +bdd.escapeColumn(table)+"."
        +bdd.escapeColumn("id")
        +" = "+std::to_string(id)
        +") ";

        Query* q = bdd.query(q_str);

        T* res = new T();
        if(not q->getObj(*res,max_depth))
        {
            #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
            std::cerr<<ROUGE<<"[GET OBJ] SQLObject<T>::_get_ptr(const unsigned int id,int max_depth) failed"<<BLANC<<std::endl;
            #endif
            delete res;
            res = 0;
        }
        delete q;
        return res;
    };

    template<typename T>
    std::list<typename Cache<T>::type_ptr> SQLObject<T>::all(Bdd& bdd,int max_depth)
    {
        std::list<typename Cache<T>::type_ptr> results;
        query(bdd).get(results,max_depth);
        return results;
    };

    template<typename T>
    QuerySet<T> SQLObject<T>::query(Bdd& bdd)
    {
        return QuerySet<T>(bdd);
    }


    template<typename T>
    bool SQLObject<T>::save(Bdd& bdd,bool recursive)
    {
        if(recursive)//save all FK
        {
            for(VFK* fk : fks)
                fk->save(bdd,recursive);
        }
        else//save or create all FK needed (not null)
        {
            for(VFK* fk : fks)
            {
                VFK& fk_tmp = *fk;
                if(fk_tmp.nullable == false and (fk_tmp.fk <=0 or fk_tmp.modify == true))
                    fk_tmp.save(bdd,recursive);
            }
        }

        if(pk <= 0)
        {
            return bdd.save(table,pk,attrs);
        }
        else
        {
            return bdd.update(table,pk,attrs);
        }
    }

    template<typename T>
    bool SQLObject<T>::del(Bdd& bdd,bool recursive)
    {
        bool res =true;
        if(bdd.del(table,pk))
        {
            cache.del(pk);
            pk = -1;
            if(recursive)
            {
                for(VFK* fk : fks)
                {
                    bool tmp = fk->del(bdd,recursive);
                    res = res && tmp;
                }
            }
            return res;
        }
        return false;
    };

    template<typename T>
    bool SQLObject<T>::create(Bdd& bdd)
    {
        #if ORM_DEBUG & ORM_DEBUG_CREATE_TABLE
        std::cerr<<MAGENTA<<"[CREATE] create table "<<table<<BLANC<<std::endl;
        #endif
        //TODO
        return false;
    }

    template<typename T>
    bool SQLObject<T>::del(Bdd& bdd)
    {
        #if ORM_DEBUG & ORM_DEBUG_DROP_TABLE
        std::cerr<<MAGENTA<<"[DROP] drop table "<<table<<BLANC<<std::endl;
        #endif
        //TODO
        return false;
    }

    template<typename T>
    bool SQLObject<T>::clear(Bdd& bdd)
    {
        #if ORM_DEBUG & ORM_DEBUG_TRUNCATE_TABLE
        std::cerr<<MAGENTA<<"[TRUNCATE] truncate table "<<table<<BLANC<<std::endl;
        #endif
        //TODO
        return false;
    }

    template<typename T>
    void SQLObject<T>::nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,Bdd& bdd)
    {
        q_str+= bdd.escapeColumn(prefix)+"."+bdd.escapeColumn("id")+" AS "+JOIN_ALIAS(prefix,"id");
        
        const int size = column_attrs.size();

        for(int i=0;i<size;++i)
        {
            q_str+= column_attrs[i]->makeName(bdd,prefix,max_depth);
        }
    }

    template<typename T>
    void SQLObject<T>::nameTables(std::string& q_str,const std::string& prefix,int max_depth,Bdd& bdd)
    {
        const std::string table_alias = MAKE_PREFIX(prefix,table);
        const std::string escaped_table_alias = bdd.escapeColumn(table_alias);

        q_str+=escaped_table_alias+" AS "+escaped_table_alias;

        if(--max_depth>=0)
            makeJoin(q_str,table_alias,max_depth,bdd);
    }

    template<typename T>
    void SQLObject<T>::makeJoin(std::string& q_str,const std::string& prefix,int max_depth,Bdd& bdd)
    {
        const int size = column_fks.size();
        --max_depth;
        for(int i=0;i<size;++i)
        {

            const SQLObjectBase& object = column_fks[i]->getObject(bdd);
            /*if (&object == NULL)
                continue;*/
            const std::string& col = column_fks[i]->getcolumn();
            const std::string table_alias = MAKE_PREFIX(prefix,col);

            q_str+= "\nLEFT JOIN "+object.getTable()+" AS "+table_alias
                +" ON ("
                +bdd.escapeColumn(prefix)+"."+bdd.escapeColumn(col)
                +" = "+bdd.escapeColumn(table_alias)+"."+bdd.escapeColumn("id")
                +")";

            if(max_depth>=0)
                object._makeJoin(q_str,table_alias,max_depth,bdd);
        }
    }

    template<typename T>
    void SQLObject<T>::_nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,Bdd& bdd)const
    {
        SQLObject<T>::nameAttrs(q_str,prefix,max_depth,bdd);
    }

    template<typename T>
    void SQLObject<T>::_nameTables(std::string& q_str,const std::string& prefix,int max_depth,Bdd& bdd)const
    {
        SQLObject<T>::nameTables(q_str,prefix,max_depth,bdd);
    }

    template<typename T>
    void SQLObject<T>::_makeJoin(std::string& q_str,const std::string& prefix,int max_depth,Bdd& bdd)const
    {
        SQLObject<T>::makeJoin(q_str,prefix,max_depth,bdd);
    }

    template<typename T>
    void SQLObject<T>::incDepth(int& depth,int max_depth)
    {
        depth+= (1 + column_attrs.size()); //id + attrs

        const int _size = column_fks.size();
        for(int i=0;i<_size;++i)
            column_fks[i]->incDepth(depth,max_depth);
    }
};
