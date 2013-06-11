#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

//#include <ORM/models/SQLObjectBase.hpp>
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

        protected:
            const static std::string table;
            T& owner;
            std::list<std::shared_ptr<U> > linked;

            //MAKE_STATIC_COLUM(owner);
            //MAKE_STATIC_COLUM(linked);
            //FK<U> linked;
    };
}
#include <ORM/fields/ManyToMany.tpl>
#endif
