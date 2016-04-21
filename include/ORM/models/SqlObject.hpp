#ifndef ORM_SqlOBJECT_HPP
#define ORM_SqlOBJECT_HPP

//orm::
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/fields/private/VFK.hpp>
#include <ORM/core/Cache.hpp>
#include <ORM/core/macros.hpp>
#include <ORM/core/Register.hpp>
//std::
#include <memory>

/**
needed for multiple inheritance from std::enable_shared_from_this<T>
struct A: virtual_enable_shared_from_this<A> {};
struct B: virtual_enable_shared_from_this<B> {};
struct Z: A, B { };
int main() {
   std::shared_ptr<Z> z = std::make_shared<Z>();
   std::shared_ptr<B> b = z->B::shared_from_this();
}
*/
struct virtual_enable_shared_from_this_base: std::enable_shared_from_this<virtual_enable_shared_from_this_base>
{
   virtual ~virtual_enable_shared_from_this_base() {}
};

template<typename T>
struct virtual_enable_shared_from_this: virtual virtual_enable_shared_from_this_base
{
   std::shared_ptr<T> shared_from_this()
   {
      return std::dynamic_pointer_cast<T>(virtual_enable_shared_from_this_base::shared_from_this());
   }
};



namespace orm
{

    class DB;
    template<typename T> class QuerySet;
    /**
    * \brief a class to manage customs sql objects
    * Note : T is your model
    *
    * Usage : 
    * \code
    * class A : SqlObject<A>
    * { 
    * ...
    * MAKE_STATIC_COLUMN(A,"table_name",...)
    * };
    * \endcode
    **/
    template<typename T>
    class SqlObject : public SqlObjectBase, public virtual_enable_shared_from_this<T>
    {
        public:
            using pointer_array = typename QuerySet<T>::pointer_array;
            using pointer = typename Cache<T>::pointer;


            SqlObject(const SqlObject&) = delete;
            SqlObject& operator=(const SqlObject&) = delete;
            
            /**
            * \brief make a SqlObject
            **/
            SqlObject();

            template<typename ... Args>
            static pointer create(Args&& ... args);

            /**
            * \brief create a new object from query
            *
            * \param query the query row of the object
            * \param prefix column index
            * \param max_depth maximum depth of constrution
            *
            * \return the new object (need to delete it by hand)
            **/
            static pointer createFromDB(const Query& query,int& prefix,int max_depth);

            /**
            * \brief shortcut for T::query().filter(id,"exact","id").get(obj)
             * \param db the db to fetch
            * \return the object of pk id
            *
            * Note : if the return obj as a pk of -1 : fail
            **/
            static pointer get(const unsigned int& id,DB& db= *default_connection,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
            * \brief shortcut for T::query().get(list)
             * \param db the db to fetch
            *
            * \return all the objects T
            **/
            static pointer_array all(DB& db = *default_connection,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
            * \brief create a queryset for the objet. Use it to make your query
             * \param db the db to fetch
            *
            * \return The tempory queryset. use chaine function, or copy it
            **/
            static QuerySet<T> query(DB& db = *default_connection);

            /**
            * \brief save/update the object in data base
            *
             * \param db the db to fetch
            * \param recursive recursive?
            *
            * \return false if fail
            **/
            virtual bool save(bool recursive=false,DB& db = *default_connection) override /*final*/;

            /**
            * \brief delete the object from de data base
            *
             * \param db the db to fetch
            * \param recursive recursive?
            * \return false if fail
            **/
            virtual bool del(bool recursive=false,DB& db = *default_connection) override;


            pointer as_pointer();


            /**
             * \brief create the table
             * \todo
             * \return true if success
             */
            static bool createTable(DB& db = *default_connection);

            /**
             * \brief drop the table
             * \todo
             * \return true if success
             */
            static bool dropTable(DB& db = *default_connection);

            /**
             * \brief truncate the table
             * \todo
             * \return true if success
             */
            static bool clearTable(DB& db = *default_connection);

            /**
            \brief return the default database registred for the object
            */
            virtual DB& getDefaultDataBase()const override;

            static  DB* default_connection; ///< db use to stor the object


        protected:
            const static std::string table; ///< the table name
            static Cache<T> cache; ///< the cache containing the objects

            /**
            * \return the table name
            **/
            virtual const std::string& getTable()const override {return table;};
            
            /**
             * \brief make the attrs columns alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            /**
             * \brief make the table alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            /**
             * \brief make the table alias of fk with join
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

        private:

            template<typename U> friend class Cache;
            template<typename U> friend class Register;
            template<typename U,typename V> friend class ManyToMany;
            template<typename RELATED,typename U> friend class Filter;
            friend class FKBase<T>;
            friend class Query;
            friend class QuerySet<T>;

            static Register<T> _register; ///< use to auto register the class
            static std::vector<const VAttr*> column_attrs; ///< attr of the class
            static std::vector<VFK*> column_fks; ///< fk of the class

            /**
            * \brief make the attrs columns alias
            *
             * \param db the db to fetch
            * \param q_str string query to add the alias
            * \param prefix prefix column name
            * \param max_depth maximun depth of constrution
            **/
            static void nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db);

            /**
             * \brief make the table alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            static void nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db);

            /**
             * \brief make the table alias of fk with join
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            static void makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db);


            /**
            * \brief Create a abject of pk id
            *
             * \param db the db to fetch
            * \param id the pk of the object
            * \param max_depth maximun depth of construction
            *
            * \return the objet (delete it by hand)
            **/
            static pointer _get_ptr(const unsigned int id,DB& db,int max_depth);

            /**
            * \brief use by the cache to increment depth
            **/
            static void incDepth(int& depth,int max_depth);

    };
};

#include <ORM/models/SqlObject.tpl>
#endif
