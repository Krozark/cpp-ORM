#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

#include <ORM/models/SQLObject.hpp>
#include <ORM/backends/Query.hpp>
#include <string>
#include <list>
#include <memory>

namespace orm
{

    /**
     * \todo faire la classe
     **/
    template<typename T,typename U>
    class ManyToMany
    {
        public:
            ManyToMany(T& owner);
            //void registerAttr(SQLObjectBase&);
            const std::list<std::shared_ptr<U> >& all(bool maj=false);
            //Query* filter();
            void add(const U&);

            template<typename ... Args>
            void add(const Args& ... args);

            static  Bdd* bdd_used;

        protected:
            bool modify;
            const static std::string table;
            T& owner;
            std::list<std::shared_ptr<U> > linked;

            MAKE_STATIC_COLUM(owner,linked)
            //FK<U> linked;
    };
}
#include <ORM/fields/ManyToMany.tpl>
#endif
