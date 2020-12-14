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
    template<typename OWNER,typename RELATED>
    class ManyToMany: public DataBaseMixin<ManyToMany<OWNER,RELATED>>
    {
        public:
            using query_type = M2MQuerySet<OWNER,RELATED>;
                
            ManyToMany(OWNER& owner);
            //void registerAttr(SqlObjectBase&);

            /**
             * \brief create a queryset for the objet. Use it to make your query
             * \param db the db to fetch
             *
             * \return The tempory queryset. use chaine function, or copy it
             **/
            query_type query(DB& db= DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase())const;

            /**
            * \brief shortcut for T::query().get(list)
             * \param db the db to fetch
            *
            * \return all the objects T
            **/
            typename RELATED::pointer_array all(DB& db= DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase(),int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief add a object in the relation
             *
             * \param obj the object to add.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            //bool add(const RELATED& obj,DB& db=staticGetDefaultDataBase());

            /**
             * \brief add a object in the relation
             *
             * \param obj the object to add.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            bool add(const typename RELATED::pointer& obj,DB& db= DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase());

            /**
             * \brief remove a object in the relation
             *
             * \param obj the object to remove.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            void remove(const RELATED& obj,DB& db= DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase());

            /**
             * \brief remove a object in the relation
             *
             * \param obj the object to remove.
             * \param db the db to fetch
             * Note : the object must have be save in database.
             **/
            void remove(const typename RELATED::pointer& obj,DB& db= DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase());

            /**
             * \brief create the table
             * \todo
             * \return true if success
             */
            static bool createTable(DB& db = DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase());

            /**
             * \brief drop the table
             * \todo
             * \return true if success
             */
            static bool dropTable(DB& db = DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase());

            /**
             * \brief truncate the table
             * \todo
             * \return true if success
             */
            static bool clearTable(DB& db = DataBaseMixin<ManyToMany<OWNER,RELATED>>::staticGetDefaultDataBase());


            const static std::string _table; ///< table of the object

        protected:
            friend class M2MQuerySet<OWNER,RELATED>;

            const OWNER& _owner; ///< owner of the m2m relation

            ORM_MAKE_STATIC_COLUMN(_owner,_linked,_related) ///< colum names of the tables

            /**
            * \brief make the attrs columns alias
            *
            * \param q_str string query to add the alias
             * \param db the db to fetch
            * \param max_depth maximun depth of constrution
            **/
            static void _nameAttrs(std::string& q_str,int max_depth,DB& db);

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
            static M2MRegister<OWNER,RELATED> _register;

            typename RELATED::pointer_array _cache;
            bool _adds;

    };

    /*
    template <typename OWNER,typename RELATED,typename T, typename ... Args>
    FilterSet<ManyToMany<OWNER,RELATED>> M2MQ(T&& value,Args&& ... args);
    */

}
#include <ORM/fields/ManyToMany.tpl>
#endif
