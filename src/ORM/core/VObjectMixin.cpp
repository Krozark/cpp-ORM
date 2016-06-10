#include <ORM/core/VObjectMixin.hpp>

namespace orm
{
    
    VObjectMixin::~VObjectMixin()
    {
    }

    bool VObjectMixin::save(bool recursive)
    {
        return this->save(recursive, getDefaultDataBase());
    }

    bool VObjectMixin::del(bool recursive)
    {
        return this->del(recursive, getDefaultDataBase());
    }
}
