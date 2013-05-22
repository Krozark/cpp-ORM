
#include "SQLObject.hpp"
namespace orm
{
    template<typename T>
    int Query::getObj(SQLObject<T>& obj)
    {
        if(not executed)
            execute();
        
        if (next())
            return obj.loadFromBdd(*this);
        return 0;
    };

    template<typename T>
    int Query::getObj(const SQLObject<T>& base,std::list<SQLObject<T> >& objs)
    {
        if(not executed)
            execute();
        int res = 0;
        while(next())
        {
            objs.emplace_back(base.createFromBdd(*this));
            ++res;
        }   
        return res;     
    };
};
