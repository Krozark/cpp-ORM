#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/Filter.hpp>

const std::string TABLE_ALIAS_SEPARATOR("__");

inline const std::string JOIN_ALIAS(const std::string& prefix,const std::string& colum)
{
    return prefix+TABLE_ALIAS_SEPARATOR+colum;
};

inline const std::string MAKE_PREFIX(const std::string& prefix,const std::string& table)
{
    return (prefix.size()>0)?JOIN_ALIAS(prefix,table):table;
};

namespace orm
{
    template<typename T>
    SQLObject<T>::SQLObject()
    {
    };

    template<typename T>
    T* SQLObject<T>::createFromBdd(const Query& query)
    {
        T* res = new T();
        if(not res->loadFromBdd(query))
        {
            delete res;
            res = 0;
        }
        return res;
    };

    template<typename T>
    typename Cache<T>::type_ptr& SQLObject<T>::get(const unsigned int& id,int max_depth)
    {
        return cache.getOrCreate(id,max_depth);
    }
    
    template<typename T>
    T* SQLObject<T>::_get_ptr(const unsigned int id,int max_depth)
    {
        if(max_depth <0)
            return 0;

        std::string q_str ="SELECT ";
        nameAttrs(q_str,table,max_depth);
                                    
        q_str+="\nFROM ";
        nameTables(q_str,"",max_depth);

        q_str+=" \nWHERE ("
        +bdd_used->escape_colum(table)+"."
        +bdd_used->escape_colum("id")+ " "
        +bdd_used->escape_value("exact",std::to_string(id));
        q_str+=") ";

        Query* q = bdd_used->query(q_str);

        T* res = new T();
        if(not q->getObj(*res))
        {
            delete res;
            res = 0;
        }
        delete q;
        return res;
    };

    /*template<typename T>
    template<typename U>
    std::list<typename Cache<T>::type_ptr> SQLObject<T>::filter(const std::string& colum,const std::string& ope,const U& value)
    {
        return filter(Filter(colum,ope,value));
    }


    template<typename T>
    std::list<typename Cache<T>::type_ptr> SQLObject<T>::filter(const Filter& filter)
    {
        std::string q_str ="SELECT ";
        nameAttrs(q_str);

        q_str+="\nFROM ";
        nameTables(q_str);

        q_str+=+" \nWHERE ( "
            +filter.colum+" "
            +bdd_used->escape_value(filter.ope,filter.value);

        nameFks(q_str);
        q_str+=") ";

        Query* q = bdd_used->query(q_str);
        std::list<typename Cache<T>::type_ptr> res;
        q->getObj(res);
        delete q;
        return res;
    }

    template<typename T>
    std::list<typename Cache<T>::type_ptr> SQLObject<T>::filter(const std::list<Filter>& filters)
    {
        int size = filters.size();

        if(size >0)
        {
            std::string q_str ="SELECT ";
            nameAttrs(q_str);

            q_str+="\nFROM ";
            nameTables(q_str);

            q_str+=" \nWHERE ( ";
            bool first = true;

            for(const Filter& filter:filters)
            {
                if(not first)
                    q_str+="\nAND ";
                
                q_str+=filter.colum+" "
                    +bdd_used->escape_value(filter.ope,filter.value);

                first = false;
            }
            nameFks(q_str);
            q_str+=" )";

            std::list<typename Cache<T>::type_ptr> res;
            Query* q = bdd_used->query(q_str);
            q->getObj(res);
            delete q;
            return res;
        }
        //no filters
        return all();
    }

    template<typename T>
    std::list<typename Cache<T>::type_ptr> SQLObject<T>::all()
    {
        std::string q_str ="SELECT ";
        nameAttrs(q_str);
                                    
        q_str+="\nFROM ";
        nameTables(q_str);

        q_str+=" \nWHERE ( 1=1";
        nameFks(q_str);
        q_str+=") ";

        Query* q = bdd_used->query(q_str);
        std::list<typename Cache<T>::type_ptr> res;
        q->getObj(res);
        delete q;
        return res;
    };*/

    template<typename T>
    bool SQLObject<T>::save(bool recursive,bool force)
    {
        if (not force)
            force = (pk == -1);

        if(recursive)
        {
            for(VFK* fk : fks)
                fk->save(recursive,force);
        }

        if(force)
            return bdd_used->save(table,pk,attrs);
        else
            return bdd_used->update(table,pk,attrs);
    }

    template<typename T>
    bool SQLObject<T>::del()
    {
        if(bdd_used->del(table,pk))
        {
            cache.del(pk);
            pk = -1;
            return true;
        }
        return false;
    };

    template<typename T>
    void SQLObject<T>::nameAttrs(std::string& q_str,const std::string& prefix,int max_depth)
    {
        q_str+= bdd_used->escape_colum(prefix)+"."+bdd_used->escape_colum("id")+" AS "+bdd_used->escape_value(JOIN_ALIAS(prefix,"id"));
        
        {
            const int size = colum_attrs.size();
            for(int i=0;i<size;++i)
            {
                const std::string& col = colum_attrs[i]->getColum();
                q_str+= ", "
                +bdd_used->escape_colum(prefix)+"."+bdd_used->escape_colum(col)
                +" AS "
                +bdd_used->escape_value(JOIN_ALIAS(prefix,col));
            }
        }
        if(--max_depth <0)
            return;
        
        const int size = colum_fks.size();
        for(int i=0;i<size;++i)
        {
            const SQLObjectBase& object = colum_fks[i]->getObject();
            const std::string& col = colum_fks[i]->getColum();
            const std::string table_alias = MAKE_PREFIX(prefix,col);

            q_str+="\n,";
            object._nameAttrs(q_str,table_alias,max_depth);
        }
    }

    template<typename T>
    void SQLObject<T>::nameTables(std::string& q_str,const std::string& prefix,int max_depth)
    {
        const std::string table_alias = MAKE_PREFIX(prefix,table);
        const std::string escaped_table_alias = bdd_used->escape_colum(table_alias);

        q_str+=escaped_table_alias+" AS "+escaped_table_alias;

        if(--max_depth>=0)
            makeJoin(q_str,table_alias,max_depth);
    }

    template<typename T>
    void SQLObject<T>::makeJoin(std::string& q_str,const std::string& prefix,int max_depth)
    {
        const int size = colum_fks.size();
        --max_depth;
        for(int i=0;i<size;++i)
        {

            const SQLObjectBase& object = colum_fks[i]->getObject();
            const std::string& col = colum_fks[i]->getColum();
            const std::string table_alias = MAKE_PREFIX(prefix,col);

            q_str+= "\nINNER JOIN "+object.getTable()+" AS "+table_alias
                +" ON ("
                +bdd_used->escape_colum(prefix)+"."+bdd_used->escape_colum(col)
                +bdd_used->operators.at("exact")
                +bdd_used->escape_colum(table_alias)+"."+bdd_used->escape_colum("id")
                +")";

            if(max_depth>=0)
                object._makeJoin(q_str,table_alias,max_depth);
        }
    }

    template<typename T>
    void SQLObject<T>::_nameAttrs(std::string& q_str,const std::string& prefix,int max_depth)const
    {
        SQLObject<T>::nameAttrs(q_str,prefix,max_depth);
    }

    template<typename T>
    void SQLObject<T>::_nameTables(std::string& q_str,const std::string& prefix,int max_depth)const
    {
        SQLObject<T>::nameTables(q_str,prefix,max_depth);
    }

    template<typename T>
    void SQLObject<T>::_makeJoin(std::string& q_str,const std::string& prefix,int max_depth)const
    {
        SQLObject<T>::makeJoin(q_str,prefix,max_depth);
    }
};
