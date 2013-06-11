#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

#include <ORM/models/SQLObject.hpp>
#include <string>
#include <list>
#include <memory>

namespace orm
{
    template<typename T,typename U>
    class ManyToMany
    {
        public:
            ManyToMany(T& owner);
            //void registerAttr(SQLObjectBase&);
            std::list<std::shared_ptr<U> >& all(bool maj=false);

            static  Bdd* bdd_used;

        protected:
            const static std::string table;
            T& owner;
            std::list<std::shared_ptr<U> > linked;

            MAKE_STATIC_COLUM(owner,linked)
            //FK<U> linked;
    };
}
#include <ORM/fields/ManyToMany.tpl>
#endif
