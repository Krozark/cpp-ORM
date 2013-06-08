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
                                    
        q_str+="\nFROM ";
        res->nameTables(q_str);

        q_str+=" \nWHERE ("
        +bdd_used->escape_colum(table)+"."
        +bdd_used->escape_colum("id")+ " "
        +bdd_used->escape_value("exact",std::to_string(id));
        res->nameFks(q_str);
        q_str+=") ";

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
        T* tmp = new T();

        std::string q_str ="SELECT ";
        tmp->nameAttrs(q_str);

        q_str+="\nFROM ";
        tmp->nameTables(q_str);

        q_str+=+" \nWHERE ( "
            +filter.colum+" "
            +bdd_used->escape_value(filter.ope,filter.value);
        tmp->nameFks(q_str);
        q_str+=") ";

        delete tmp;

        Query* q = bdd_used->query(q_str);
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
            T* tmp = new T();

            std::string q_str ="SELECT ";
            tmp->nameAttrs(q_str);

            q_str+="\nFROM ";
            tmp->nameTables(q_str);

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
            tmp->nameFks(q_str);
            q_str+=" )";

            delete tmp;

            std::list<T*> res;
            Query* q = bdd_used->query(q_str);
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
        T* tmp = new T();

        std::string q_str ="SELECT ";
        tmp->nameAttrs(q_str);
                                    
        q_str+="\nFROM ";
        tmp->nameTables(q_str);

        q_str+=" \nWHERE ( 1=1";
        tmp->nameFks(q_str);
        q_str+=") ";

        delete tmp;

        Query* q = bdd_used->query(q_str);
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
