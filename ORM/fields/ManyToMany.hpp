#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

#include <ORM/models/SQLObject.hpp>
#include <ORM/backends/Query.hpp>
#include <string>
#include <list>
#include <memory>

namespace orm
{

    template<typename T,typename U,typename V> class M2MQuerySet;
    /**
     * \todo faire la classe
     **/
    template<typename OWNER,typename RELATED>
    class ManyToMany
    {
        public:
            ManyToMany(OWNER& owner);
            //void registerAttr(SQLObjectBase&);

            /**
             * \brief create a queryset for the objet. Use it to make your query
             *
             * \return The tempory queryset. use chaine function, or copy it
             **/
            M2MQuerySet<ManyToMany<OWNER,RELATED>,OWNER,RELATED> query();

            /**
            * \brief shortcut for T::query().get(list)
            *
            * \return all the objects T
            **/
            std::list<typename Cache<RELATED>::type_ptr> all(int max_depth=ORM_DEFAULT_MAX_DEPTH);
            
            void add(const RELATED& obj);

            template<typename ... Args>
            void add(const Args& ... args);

            static  Bdd* bdd_used;
            const static std::string table;

        protected:
            friend class M2MQuerySet<ManyToMany<OWNER,RELATED>,OWNER,RELATED>;

            bool modify;
            const OWNER& owner;

            MAKE_STATIC_COLUMN(owner,linked,related)
            //FK<U> linked;

            /**
            * \brief make the attrs columns alias
            *
            * \param q_str string query to add the alias
            * \param max_depth maximun depth of constrution
            **/
            static void nameAttrs(std::string& q_str,int max_depth);
             /**
             * \brief make the table alias
             *
             * \param q_str string query to add the alias
             * \param max_depth maximun depth of constrution
             **/
            static void nameTables(std::string& q_str,int max_depth);

            /**
             * \brief make the table alias of fk with join
             *
             * \param q_str string query to add the alias
             * \param max_depth maximun depth of constrution
             **/
            static void makeJoin(std::string& q_str,int max_depth);

    };
}
#include <ORM/fields/ManyToMany.tpl>
#endif
