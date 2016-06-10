#ifndef ORM_SqlOBJECTBASE_HPP
#define ORM_SqlOBJECTBASE_HPP

#include <vector>
#include <ostream>

#include <ORM/externals.hpp>
#include <ORM/core/macros.hpp>
#include <ORM/core/VObjectMixin.hpp>
#include <memory>


namespace orm
{
    class Query;
    class VAttr;
    class DB;
    class VFK;

    /**
     * \brief Base classe to manage SqlObjects. Usfull to store them in containers
     **/
    class SqlObjectBase : public VObjectMixin
    {
        public:
            typedef std::shared_ptr<SqlObjectBase> pointer;

            /**
             * \brief Make a SqlObjectBase
             **/
            SqlObjectBase();

            SqlObjectBase(const SqlObjectBase&)=delete;
            SqlObjectBase& operator=(const SqlObjectBase&)=delete;


            /**
             * \return the object pk
             */
            int getPk()const;

            /**
            \brief get all the attributs of the instance
            **/
            std::vector<VAttr*>& getAttributes();

            /**
            \brief get the attributs of the instance named name
            \return nullptr if not existe
            **/
            VAttr* getAttribute(const std::string& name);

            /**
             * \brief Display the object in json
             **/
            friend std::ostream& operator<<(std::ostream& output,const SqlObjectBase& self);


            ORM_MAKE_STATIC_COLUMN(pk);


        protected:
            friend class DB;
            friend class VFK;
            friend class VAttr;
            template<typename T> friend class FKBase;
            template<typename T> friend class Register;
            template<typename T> friend class SqlObject;
            template<typename T,typename U> friend class M2MQuerySet;
            template<typename T,typename U> friend class ManyToMany;
            template<typename U> friend class Cache;


            /**
             * \brief prepare the object before save it in DB (new object only)
             * Note : do nothing by default.
             */
            virtual void _beforeSave();

            /**
             * \brief prepare the object after save it in DB (new object only)
             * Note : do nothing by default.
             */
            virtual void _afterSave();

            /**
             * \brief prepare the object before update it in DB (not new object only)
             * Note : do nothing by default.
             */
            virtual void _beforeUpdate();

            /**
             * \brief prepare the object after update it in DB (not new object only)
             * Note : do nothing by default.
             */
            virtual void _afterUpdate();

            /**
             * \brief prepare the object before loading it from the DB
             * Note : do nothing by default.
             */
            virtual void _beforeLoad();

            /**
             * \brief prepare the object after loading it in from the DB
             * Note : do nothing by default.
             */
            virtual void _afterLoad();

            /**
             * \brief create the object using the query
             *
             * \param  query The executed query row
             * \param max_depth the maximun depth of constrution
             *
             * \return false if fail
             **/
            virtual bool _loadFromDB(const Query& query,int max_depth);

            /**
             * \brief create the object using the query
             *
             * \param  query The executed query row
             * \param max_depth the maximun depth of constrution
             * \param prefix column number
             *
             * \return false if fail
             **/
            virtual bool _loadFromDB(const Query& query,int& prefix,int max_depth);


        private:
            int pk; ///< the object pf
            std::vector<VAttr*> _attributsVector; ///< the object attrs
            std::vector<VFK*> _fkAttributsVector; ///< the object FK

            /**
            * \brief make the attrs columns alias
            *
            * \param db the db to fetch
            * \param q_str string query to add the alias
            * \param prefix prefix column name
            * \param max_depth maximun depth of constrution
            **/
            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const =0;

            /**
             * \brief make the table alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const =0;

            /**
             * \brief make the table alias of fk with join
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const =0;

    };
};


#endif
