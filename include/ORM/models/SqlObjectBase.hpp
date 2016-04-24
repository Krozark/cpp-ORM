#ifndef ORM_SqlOBJECTBASE_HPP
#define ORM_SqlOBJECTBASE_HPP

#include <vector>
#include <ostream>

#include <ORM/externals.hpp>
#include <ORM/core/macros.hpp>
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
    class SqlObjectBase
    {
        public:
            typedef std::shared_ptr<SqlObjectBase> pointer;

            /**
             * \brief Make a SqlObjectBase
             **/
            SqlObjectBase();

            virtual ~SqlObjectBase();

            SqlObjectBase(const SqlObjectBase&)=delete;
            SqlObjectBase& operator=(const SqlObjectBase&)=delete;



            /**
             * \brief save/update the object in data base
             *
             * \param db the db to fetch
             * \param recursive recursive?
             *
             * \return false if fail
             **/
            virtual bool save(bool recursive, DB& db) = 0;

            /**
            * \brief save/update the object in data base
            * overload of save, but use default dadabase
            *
            * \param recursive recursive?
            *
            * \return false if fail
            **/
            bool save(bool recursive = false);


            /**
             * \brief delete the object from de data base
             *
             * \param db the db to fetch
             * \param recursive recursive?
             * \return false if fail
             **/
            virtual bool del(bool recursive, DB& db) = 0;

            /**
            * \brief delete the object from de data base
            * overload of del, but use default dadabase
            *
            * \param recursive recursive?
            *
            * \return false if fail
            **/
            bool del(bool recursive = false);


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
            \brief return the default database registred for the object
            */
            virtual DB& getDefaultDataBase()const = 0;

            /**
             * \brief Display the object in json
             **/
            friend std::ostream& operator<<(std::ostream& output,const SqlObjectBase& self);


            ORM_MAKE_STATIC_COLUMN(pk);

            /**
            * \return the table name
            **/
            virtual const std::string& getTable() const = 0;


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
            virtual void before_save();

            /**
             * \brief prepare the object after save it in DB (new object only)
             * Note : do nothing by default.
             */
            virtual void after_save();

            /**
             * \brief prepare the object before update it in DB (not new object only)
             * Note : do nothing by default.
             */
            virtual void before_update();

            /**
             * \brief prepare the object after update it in DB (not new object only)
             * Note : do nothing by default.
             */
            virtual void after_update();

            /**
             * \brief prepare the object before loading it from the DB
             * Note : do nothing by default.
             */
            virtual void before_load();

            /**
             * \brief prepare the object after loading it in from the DB
             * Note : do nothing by default.
             */
            virtual void after_load();

            /**
             * \brief create the object using the query
             *
             * \param  query The executed query row
             * \param max_depth the maximun depth of constrution
             *
             * \return false if fail
             **/
            virtual bool loadFromDB(const Query& query,int max_depth);

            /**
             * \brief create the object using the query
             *
             * \param  query The executed query row
             * \param max_depth the maximun depth of constrution
             * \param prefix column number
             *
             * \return false if fail
             **/
            virtual bool loadFromDB(const Query& query,int& prefix,int max_depth);


        private:
            int pk; ///< the object pf
            std::vector<VAttr*> attrs; ///< the object attrs
            std::vector<VFK*> fks; ///< the object FK

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
