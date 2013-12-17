#ifndef ORM_SQLOBJECTBASE_HPP
#define ORM_SQLOBJECTBASE_HPP

#include <vector>
#include <ostream>

#include <ORM/externals.hpp>

namespace orm
{
    class Query;
    class VAttr;
    class Bdd;
    class VFK;
    template<typename T> class Register;
    template<typename T> class FKBase;
    template<typename T> class SQLObject;
    template<typename T,typename U,typename V> class M2MQuerySet;

    /**
     * \brief Base classe to manage SQLObjects. Usfull to store them in containers
     **/
    class SQLObjectBase
    {
        public:
            /**
             * \brief Make a SQLObjectBase
             **/
            SQLObjectBase();

            virtual ~SQLObjectBase(){};

            SQLObjectBase(const SQLObjectBase&)=delete;
            SQLObjectBase& operator=(const SQLObjectBase&)=delete;


            /**
             * \brief save/update the object in data base
             *
             * \param recursive recursive?
             *
             * \return false if fail
             **/
            virtual bool save(bool recursive=false) = 0;

            /**
             * \brief delete the object from de data base
             *
             * \param recursive recursive?
             * \return false if fail
             **/
            virtual bool del(bool recursive=false) = 0;


            /**
             * \return the object pk
             */
            int getPk()const;

            /**
             * \brief Display the object in json
             **/
            friend std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self);


        protected:
            friend class Bdd;
            friend class VFK;
            friend class VAttr;
            template<typename T> friend class FKBase;
            template<typename T> friend class Register;
            template<typename T> friend class SQLObject;
            template<typename T,typename U,typename V> friend class M2MQuerySet;

            int pk; ///< the object pf
            std::vector<VAttr*> attrs; ///< the object attrs
            std::vector<VFK*> fks; ///< the object FK

            /**
             * \brief create the object using the query
             *
             * \param  query The executed query row
             * \param max_depth the maximun depth of constrution
             *
             * \return false if fail 
             **/
            bool loadFromBdd(const Query& query,int max_depth);

            /**
             * \brief create the object using the query
             *
             * \param  query The executed query row
             * \param max_depth the maximun depth of constrution
             * \param prefix column number
             *
             * \return false if fail 
             **/
            bool loadFromBdd(const Query& query,int& prefix,int max_depth);

            /**
             * \brief make the attrs columns alias
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth)const =0;

            /**
             * \brief make the table alias
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth)const =0;

            /**
             * \brief make the table alias of fk with join
             *
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth)const =0;

            /**
             * \return the table name
             **/
            virtual const std::string& getTable() const = 0;

            /**
             * \return the bdd use to store the object
             **/
            virtual const Bdd* getBdd() const = 0;
    };
};


#endif
