#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

#include <ORM/models/SqlObject.hpp>
#include <ORM/backends/Query.hpp>
#include <ORM/backends/private/M2MQuerySet.hpp>
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
            //void registerAttr(SqlObjectBase&);

            /**
             * \brief create a queryset for the objet. Use it to make your query
             * \param bdd the bdd to fetch
             *
             * \return The tempory queryset. use chaine function, or copy it
             **/
            M2MQuerySet<ManyToMany<OWNER,RELATED>,OWNER,RELATED> query(Bdd& bdd=*default_connection)const;

            /**
            * \brief shortcut for T::query().get(list)
             * \param bdd the bdd to fetch
            *
            * \return all the objects T
            **/
            std::list<typename Cache<RELATED>::type_ptr> all(Bdd& bdd=*default_connection,int max_depth=ORM_DEFAULT_MAX_DEPTH)const;
            
            /**
             * \brief add a object in the relation
             *
             * \param obj the object to add.
             * \param bdd the bdd to fetch
             * Note : the object must have be save in database.
             **/
            void add(const RELATED& obj,Bdd& bdd=*default_connection);

            /**
             * \brief add a object in the relation
             *
             * \param obj the object to add.
             * \param bdd the bdd to fetch
             * Note : the object must have be save in database.
             **/
            void add(const typename Cache<RELATED>::type_ptr& obj,Bdd& bdd=*default_connection);

            /**
             * \brief remove a object in the relation
             *
             * \param obj the object to remove.
             * \param bdd the bdd to fetch
             * Note : the object must have be save in database.
             **/
            void remove(const RELATED& obj,Bdd& bdd=*default_connection);

            /**
             * \brief remove a object in the relation
             *
             * \param obj the object to remove.
             * \param bdd the bdd to fetch
             * Note : the object must have be save in database.
             **/
            void remove(const typename Cache<RELATED>::type_ptr& obj,Bdd& bdd=*default_connection);



            static  Bdd* default_connection;///< database use to store the object
            const static std::string table; ///< table of the object

        protected:
            friend class M2MQuerySet<ManyToMany<OWNER,RELATED>,OWNER,RELATED>;

            const OWNER& owner; ///< owner of the m2m relation

            MAKE_STATIC_COLUMN(owner,linked,related) ///< colum names of the tables

            /**
            * \brief make the attrs columns alias
            *
            * \param q_str string query to add the alias
             * \param bdd the bdd to fetch
            * \param max_depth maximun depth of constrution
            **/
            static void nameAttrs(std::string& q_str,int max_depth,Bdd& bdd);

             /**
             * \brief make the table alias
             *
             * \param q_str string query to add the alias
             * \param bdd the bdd to fetch
             * \param max_depth maximun depth of constrution
             **/
            static void nameTables(std::string& q_str,int max_depth,Bdd& bdd);

            /**
             * \brief make the table alias of fk with join
             *
             * \param q_str string query to add the alias
             * \param bdd the bdd to fetch
             * \param max_depth maximun depth of constrution
             **/
            static void makeJoin(std::string& q_str,int max_depth,Bdd& bdd);

    };
}
#include <ORM/fields/ManyToMany.tpl>
#endif
