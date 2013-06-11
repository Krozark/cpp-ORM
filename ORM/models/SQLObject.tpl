#include <ORM/backends/Bdd.hpp>
#include <ORM/backends/Filter.hpp>


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
    std::shared_ptr<T>& SQLObject<T>::get(const unsigned int& id)
    {
        return cache.getOrCreate(id);
    }
    
    template<typename T>
    T* SQLObject<T>::_get_ptr(const unsigned int id)
    {
        std::string q_str ="SELECT ";
        nameAttrs(q_str);
                                    
        q_str+="\nFROM ";
        nameTables(q_str);

        q_str+=" \nWHERE ("
        +bdd_used->escape_colum(table)+"."
        +bdd_used->escape_colum("id")+ " "
        +bdd_used->escape_value("exact",std::to_string(id));

        nameFks(q_str);
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

    template<typename T>
    template<typename U>
    std::list<std::shared_ptr<T> > SQLObject<T>::filter(const std::string& colum,const std::string& ope,const U& value)
    {
        return filter(Filter(colum,ope,value));
    }


    template<typename T>
    std::list<std::shared_ptr<T> > SQLObject<T>::filter(const Filter& filter)
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
        std::list<std::shared_ptr<T> > res;
        q->getObj(res);
        delete q;
        return res;
    }

    template<typename T>
    std::list<std::shared_ptr<T> > SQLObject<T>::filter(const std::list<Filter>& filters)
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

            std::list<std::shared_ptr<T> > res;
            Query* q = bdd_used->query(q_str);
            q->getObj(res);
            delete q;
            return res;
        }
        //no filters
        return all();
    }

    template<typename T>
    std::list<std::shared_ptr<T> > SQLObject<T>::all()
    {
        std::string q_str ="SELECT ";
        nameAttrs(q_str);
                                    
        q_str+="\nFROM ";
        nameTables(q_str);

        q_str+=" \nWHERE ( 1=1";
        nameFks(q_str);
        q_str+=") ";

        Query* q = bdd_used->query(q_str);
        std::list<std::shared_ptr<T> > res;
        q->getObj(res);
        delete q;
        return res;
    };

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
            cache.map.erase(pk);
            pk = -1;
            return true;
        }
        return false;
    };

    template<typename T>
    void SQLObject<T>::nameAttrs(std::string& q_str,bool recur)
    {
        q_str+= bdd_used->escape_colum(table)+"."+bdd_used->escape_colum("id")+" AS "+bdd_used->escape_value(table+".id");
        
        {
            const int size = colum_attrs.size();
            for(int i=0;i<size;++i)
            {
                const std::string& col = colum_attrs[i]->getColum();
                q_str+= ", "+col+" AS "+bdd_used->escape_value(col);
            }
        }
        if(not recur)
            return;
        const int size = colum_fks.size();
        for(int i=0;i<size;++i)
        {
            q_str+="\n";
            const SQLObjectBase& object = colum_fks[i]->getObject();
            q_str+=",";
            object._nameAttrs(q_str);
        }
    }

    template<typename T>
    void SQLObject<T>::nameTables(std::string& q_str,bool recur)
    {
        q_str+=table;
        if(not recur)
            return;
        const int size = colum_fks.size();
        for(int i=0;i<size;++i)
        {
            q_str+=",";
            colum_fks[i]->getObject()._nameTables(q_str);
        }
    }

    template<typename T>
    void SQLObject<T>::nameFks(std::string& q_str)
    {
        const int size = colum_fks.size();

        for(int i=0;i<size;++i)
        {
            const SQLObjectBase& object = colum_fks[i]->getObject();
            q_str+= " AND "+colum_fks[i]->getColum()
                +" "+bdd_used->operators.at("exact")
                +bdd_used->escape_colum(object.getTable())+"."+bdd_used->escape_colum("id");
            object._nameFks(q_str);
        }
    }

    template<typename T>
    void SQLObject<T>::_nameAttrs(std::string& q_str)const
    {
        SQLObject<T>::nameAttrs(q_str);
    }

    template<typename T>
    void SQLObject<T>::_nameTables(std::string& q_str)const
    {
        SQLObject<T>::nameTables(q_str);
    }

    template<typename T>
    void SQLObject<T>::_nameFks(std::string& q_str)const
    {
        SQLObject<T>::nameFks(q_str);
    }
};
