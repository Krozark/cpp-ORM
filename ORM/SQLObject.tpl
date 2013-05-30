#include "Bdd.hpp"
#include "Filter.hpp"

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

        Query* q = bdd_used->query("SELECT * FROM "+
                                   table+
                                   " WHERE (id "+
                                   (*bdd_used)["exact"]+std::to_string(id)+
                                   ") ");
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
    template<>
    std::list<T*> SQLObject<T>::filter<std::string>(const std::string& colum,const std::string& ope,const std::string& value)
    {
        return SQLObject<T>::filter(Filter(colum,ope,value));
    }

    template<typename T>
    template<typename U>
    std::list<T*> SQLObject<T>::filter(const std::string& colum,const std::string& ope,const U& value)
    {
        return SQLObject<T>::filter(Filter(colum,ope,std::to_string(value)));
    }

    template<typename T>
    std::list<T*> SQLObject<T>::filter(const Filter& filter)
    {
        Query* q = bdd_used->query("SELECT * FROM "
                                   +table
                                   +" WHERE ( "
                                   +bdd_used->escape_colum(filter.colum)+" "
                                   +(*bdd_used)[filter.ope]
                                   +filter.value
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
            std::string str_q = "SELECT * FROM "
                +table
                +" WHERE ( ";
            bool first = true;
            for(Filter& filter:filters)
            {
                if(not first)
                    str_q+=" AND ";
                
                str_q+=bdd_used->escape_colum(filter.colum)+" "
                    +(*bdd_used)[filter.ope]
                    +filter.value;

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
        Query* q = bdd_used->query("SELECT * FROM "+table);
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
