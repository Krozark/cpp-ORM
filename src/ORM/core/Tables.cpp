#include <ORM/core/Tables.hpp>

namespace orm
{
    std::vector<bool(*)()> Tables::_create;
    std::vector<bool(*)()> Tables::_drop;
    std::vector<bool(*)()> Tables::_truncate;

    bool Tables::create()
    {
        bool res = false;
        //TODO beginTransaction
        for(bool(*f)() : _create)
        {
            res = f();
            if(not res)
                //TODO rollback
                return res;
        }
        //TODO commit
        return res;
    }
    
    bool Tables::del()
    {
        bool res = false;
        //TODO beginTransaction
        for(bool(*f)() : _del)
        {
            res = f();
            if(not res)
                //TODO rollback
                return res;
        }
        //TODO commit
        return res;
    }

    bool Tables::clear()
    {
        bool res = false;
        //TODO beginTransaction
        for(bool(*f)() : _clear)
        {
            res = f();
            if(not res)
                //TODO rollback
                return res;
        }
        //TODO commit
        return res;
    }
}
