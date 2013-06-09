#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

#include <ORM/models/SQLObjectBase.hpp>
#include <string>
#include <list>

namespace orm
{
    template<typename T,typename U>
    class ManyToMany
    {
        public:
            ManyToMany(T& owner);
            void registerAttr(SQLObjectBase&);

            MAKE_STATIC_COLUM(linked);



        protected:
            const static std::string table;
            T& owner;
            std::list<U> linked;

            MAKE_STATIC_COLUM(owner);
            //FK<U> linked;

    }
}
#endif
