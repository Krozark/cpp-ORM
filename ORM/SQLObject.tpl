#include "VAttr.hpp" 
#include "Bdd.hpp"

namespace orm
{
    template<typename T>
    SQLObject<T>::SQLObject() : pk(-1)
    {
    };

    template<typename T>
    bool SQLObject<T>::loadFromBdd(const Query& query)
    {
        bool res = true;
        for(VAttr* attr: attrs)
            res = res && attr->get(query);
        return res;
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
        std::list<SQLObject<T*> > res;
        q->getObj(res);
        return res;
    }

};
