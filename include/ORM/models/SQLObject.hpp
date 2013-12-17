#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

//orm::
#include <ORM/models/SQLObjectBase.hpp>
#include <ORM/fields/private/VFK.hpp>
#include <ORM/core/Cache.hpp>
#include <ORM/core/macros.hpp>
//std::
#include <memory>


namespace orm
{
    class Bdd;
    class Query;
    //class Filter;
    class VAttr;
    class VFK;
    template<typename T> class FKBase;
    template<typename T> class SQLObject;
    template<typename T> class QuerySet;

    /**
    * \brief class to register column name as static (Hack)
    **/
    template<typename T>
    class Register
    {
        public:
            /**
            * \brief constructor. Create a default object, and use it to get attrs, and fk of the class.
            * Note : default constructor have to be anable (without params)
            */
            Register()
            {
                #if ORM_DEBUG & ORM_DEBUG_REGISTER
                std::cerr<<MAGENTA<<"[Register] Table "<<T::table<<BLANC<<std::endl;
                #endif

                static T tmp;
                for(VAttr* attr: tmp.attrs)
                {
                    SQLObject<T>::column_attrs.emplace_back(attr);
                }
                for(VFK* fk: tmp.fks)
                {
                    SQLObject<T>::column_fks.emplace_back(fk);
                }
                #if ORM_DEBUG & ORM_DEBUG_REGISTER
                std::cerr<<MAGENTA<<"[Register] END Table "<<T::table<<BLANC<<std::endl;
                #endif
            }
    };

    /**
    * \brief a class to manage customs sql objects
    * Note : T is your model
    *
    * Usage : 
    * \code
    * class A : SQLObject<A>
    * { 
    * ...
    * };
    * \endcode
    **/
    template<typename T>
    class SQLObject : public SQLObjectBase
    {
        public:
            /**
            * \brief make a SQLObject
            **/
            SQLObject();

            SQLObject(const SQLObject&) = delete;
            SQLObject& operator=(const SQLObject&) = delete;

            /**
            * \brief create a new object from query
            *
            * \param query the query row of the object
            * \param prefix column index
            * \param max_depth maximum depth of constrution
            *
            * \return the new object (need to delete it by hand)
            **/
            static T* createFromBdd(const Query& query,int& prefix,int max_depth);

            /**
            * \brief shortcut for T::query().filter(id,"exact","id").get(obj)
            * \return the object of pk id
            *
            * Note : if the return obj as a pk of -1 : fail
            **/
            static typename Cache<T>::type_ptr& get(const unsigned int& id,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
            * \brief shortcut for T::query().get(list)
            *
            * \return all the objects T
            **/
            static std::list<typename Cache<T>::type_ptr> all(int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
            * \brief create a queryset for the objet. Use it to make your query
            *
            * \return The tempory queryset. use chaine function, or copy it
            **/
            static QuerySet<T> query();

            /**
            * \brief save/update the object in data base
            *
            * \param recursive recursive?
            *
            * \return false if fail
            **/
            virtual bool save(bool recursive=false);

            /**
            * \brief delete the object from de data base
            *
            * \param recursive recursive?
            * \return false if fail
            **/
            virtual bool del(bool recursive=false);

            static  Bdd* bdd_used; ///< bdd use to stor the object


        protected:
            const static std::string table; ///< the table name
            static Cache<T> cache; ///< the cache containing the objects

            /**
            * \return the table name
            **/
            virtual const std::string& getTable()const {return table;};
            
            /**
             * \return the bdd use to store the object
             **/
            virtual const Bdd* getBdd()const{return bdd_used;};
            
            /**
             * \brief make the attrs columns alias
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth)const;

            /**
             * \brief make the table alias
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth)const;

            /**
             * \brief make the table alias of fk with join
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth)const;

        private:

            template<typename U> friend class Cache;
            template<typename U> friend class Register;
            template<typename U,typename V> friend class ManyToMany;
            friend class FKBase<T>;
            friend class Query;
            friend class QuerySet<T>;

            static Register<T> _register; ///< use to auto register the class
            static std::vector<const VAttr*> column_attrs; ///< attr of the class
            static std::vector<VFK*> column_fks; ///< fk of the class

            /**
            * \brief make the attrs columns alias
            *
            * \param q_str string query to add the alias
            * \param prefix prefix column name
            * \param max_depth maximun depth of constrution
            **/
            static void nameAttrs(std::string& q_str,const std::string& prefix,int max_depth);

            /**
             * \brief make the table alias
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            static void nameTables(std::string& q_str,const std::string& prefix,int max_depth);

            /**
             * \brief make the table alias of fk with join
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            static void makeJoin(std::string& q_str,const std::string& prefix,int max_depth);

            /**
            * \brief Create a abject of pk id
            *
            * \param id the pk of the object
            * \param max_depth maximun depth of construction
            *
            * \return the objet (delete it by hand)
            **/
            static T* _get_ptr(const unsigned int id,int max_depth);

            /**
            * \brief use by the cache to increment depth
            **/
            static void incDepth(int& depth,int max_depth);
    };
};

#include <ORM/models/SQLObject.tpl>
#endif
