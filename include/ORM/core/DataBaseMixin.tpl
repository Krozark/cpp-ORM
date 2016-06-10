#include <ORM/backends/DB.hpp>

namespace orm
{
    template<typename T>
    DB& DataBaseMixin<T>::staticGetDefaultDataBase()
    {
        if(defaultDBConnection)
        {
            return *defaultDBConnection;
        }
        return *DB::Default;
    }
}
