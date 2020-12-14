#ifndef ORM_MANYTOMANY_HPP
#define ORM_MANYTOMANY_HPP

#include <ORM/core/DataBaseMixin.hpp>
#include <ORM/models/SqlObject.hpp>
#include <ORM/backends/Query.hpp>
#include <ORM/backends/private/M2MQuerySet.hpp>
#include <ORM/core/M2MRegister.hpp>
#include <string>
#include <memory>

namespace orm
{

    /**
     * \todo faire la classe
     **/
    template<typename OWNER,typename LINKED>
    class ManyToMany: public DataBaseMixin<ManyToMany<OWNER,LINKED>>
    {
        public:
            using query_type = M2MQuerySet<OWNER,LINKED>;

            ManyToMany(OWNER& owner);
            //void registerAttr(SqlObjectBase&);

            /**
             * \brief create a queryset for the objet. Use it to make your query
             * \param db the db to fetch
             *
             * \return The tempory queryset. use chaine function, or copy it
             **/
            static query_type query(DB& db= DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());

            /**
             * \brief create a queryset for the objet. Use it to make your query
             * \param db the db to fetch
             *
             * \return The tempory queryset. use chaine function, or copy it
             **/
            query_type queryOwner(DB& db= DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase())const;

            /**
            * \brief shortcut for T::query().get(list) but also stor the results in a internal cache
             * \param db the db to fetch
            *
            * \return all the objects T
            **/
            typename LINKED::pointer_array all(DB& db= DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase(),int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief add a object in the relation
             *
             * \param obj the object to add.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            //bool add(const LINKED& obj,DB& db=staticGetDefaultDataBase());

            /**
             * \brief add a object in the relation
             *
             * \param obj the object to add.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            bool add(const typename LINKED::pointer& obj,DB& db= DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());

            /**
             * \brief remove a object in the relation
             *
             * \param obj the object to remove.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            void remove(const LINKED& obj,DB& db= DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());

            /**
             * \brief remove a object in the relation
             *
             * \param obj the object to remove.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            void remove(const typename LINKED::pointer& obj,DB& db= DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());

            /**
             * Emppty the internal cache used with all() function
             */
            void clearCache();

            /**
             * \brief create the table
             * \todo
             * \return true if success
             */
            static bool createTable(DB& db = DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());

            /**
             * \brief drop the table
             * \todo
             * \return true if success
             */
            static bool dropTable(DB& db = DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());

            /**
             * \brief truncate the table
             * \todo
             * \return true if success
             */
            static bool clearTable(DB& db = DataBaseMixin<ManyToMany<OWNER,LINKED>>::staticGetDefaultDataBase());


            const static std::string _table; ///< table of the object

        protected:
            friend class M2MQuerySet<OWNER,LINKED>;

            const OWNER& _owner; ///< owner of the m2m relation

            ORM_MAKE_STATIC_COLUMN(_owner,_linked,_related) ///< colum names of the tables

            /**
            * \brief make the attrs columns alias
            *
            * \param q_str string query to add the alias
             * \param db the db to fetch
            * \param max_depth maximun depth of constrution
            **/
            static void _makeSelectOwner(std::string& q_str,int max_depth,DB& db);

            /**
            * \brief make the attrs columns alias
            *
            * \param q_str string query to add the alias
             * \param db the db to fetch
            * \param max_depth maximun depth of constrution
            **/
            static void _makeSelectLinked(std::string& q_str,int max_depth,DB& db);

             /**
             * \brief make the table alias
             *
             * \param q_str string query to add the alias
             * \param db the db to fetch
             * \param max_depth maximun depth of constrution
             **/
            static void _nameTables(std::string& q_str,int max_depth,DB& db);

            /**
             * \brief make the table alias of fk with join
             *
             * \param q_str string query to add the alias
             * \param db the db to fetch
             * \param max_depth maximun depth of constrution
             **/
            static void _makeJoin(std::string& q_str,int max_depth,DB& db);
            

        private:
            static M2MRegister<OWNER,LINKED> _register;

            typename LINKED::pointer_array _cache;
            bool _adds;

    };

    /*
    template <typename OWNER,typename LINKED,typename T, typename ... Args>
    FilterSet<ManyToMany<OWNER,LINKED>> M2MQ(T&& value,Args&& ... args);
    */

}
#include <ORM/fields/ManyToMany.tpl>
#endif
