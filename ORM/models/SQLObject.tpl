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
    T* SQLObject<T>::get(unsigned int id)
    {
        T* res = new T();

        std::string q_str ="SELECT ";

        res->nameAttrs(q_str);
                                    
        q_str+="FROM "
        +table
        +" \nWHERE ("
        +bdd_used->escape_colum(table)+"."
        +bdd_used->escape_colum("id")+ " "
        +bdd_used->escape_value("exact",std::to_string(id))
        +") ";

        Query* q = bdd_used->query(q_str);
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
    std::list<T*> SQLObject<T>::filter(const std::string& colum,const std::string& ope,const U& value)
    {
        return filter(Filter(colum,ope,value));
    }


    template<typename T>
    std::list<T*> SQLObject<T>::filter(const Filter& filter)
    {
        Query* q = bdd_used->query("SELECT * \nFROM "
                                   +table
                                   +" \nWHERE ( "
                                   +bdd_used->escape_colum(filter.colum)+" "
                                   +bdd_used->escape_value(filter.ope,filter.value)
                                   +" )"
                                  );
        std::list<T*> res;
        q->getObj(res);
        delete q;
        return res;
    }

    template<typename T>
    std::list<T*> SQLObject<T>::filter(const std::list<Filter>& filters)
    {
        int size = filters.size();

        if(size >0)
        {
            std::string str_q = "SELECT * \nFROM "
                +table
                +" \nWHERE ( ";
            bool first = true;

            for(const Filter& filter:filters)
            {
                if(not first)
                    str_q+="\nAND ";
                
                str_q+=bdd_used->escape_colum(filter.colum)+" "
                    +bdd_used->escape_value(filter.ope,filter.value);

                first = false;
            }
            str_q+=" )";

            std::list<T*> res;
            Query* q = bdd_used->query(str_q);
            q->getObj(res);
            delete q;
            return res;
        }
        //no filters
        return all();
    }

    template<typename T>
    std::list<T*> SQLObject<T>::all()
    {
        Query* q = bdd_used->query("SELECT * \nFROM "+table);
        std::list<T*> res;
        q->getObj(res);
        delete q;
        return res;
    };

    template<typename T>
    bool SQLObject<T>::save(bool force)
    {
        if (not force)
            force = (pk == -1);

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
            pk = -1;
            return true;
        }
        return false;
    };


};