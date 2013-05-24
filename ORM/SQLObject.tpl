#include "Bdd.hpp"

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
    std::list<T*> SQLObject<T>::filter()
    {

        std::list<SQLObject<T*> > res;
        return res;
    }

    template<typename T>
    std::list<T*> SQLObject<T>::all()
    {
        Query* q = bdd_used->query("SELECT * FROM "+table+" ");
        std::list<T*> res;
        q->getObj(res);
        delete q;
        return res;
    };

    template<typename T>
    bool SQLObject<T>::save(bool _new)
    {
        if (not _new)
            _new = (pk == -1);

        if(_new)
            return bdd_used->save(table,pk,attrs);
        else
            return bdd_used->update(table,pk,attrs);
    }


};
