#ifndef ORM_FKBASE_HPP
#define ORM_FKBASE_HPP

#include <ORM/fields/private/VFK.hpp>
#include <memory>

namespace orm
{
    class Query;

    /**
     * \brief Store a FK to a object
     **/
    template<typename T>
    class FKBase : public VFK
    {
        public:
            FKBase(const FKBase&) = delete;

            /**
             * \brief Destructor
             **/
            ~FKBase();


            /**
             * \brief Save or update the object on the fk
             *
             * \param bdd the bdd to fetch
             * \param recursive save recursively
             *
             * \return false if fail
             **/
            virtual bool save(Bdd& bdd,bool recursive=false);            

            /**
             * \brief Delete the object from the bdd and cache
             *  
             *  Note : whe use on object linked in other object with fks can cause trouble because of the remove of the cache
             *  Set the pk to -1
             * \param bdd the bdd to fetch
             *
             * \return fale if fail
             **/
            virtual bool del(Bdd& bdd,bool recursive=false);

            typedef T type; ///< Type of stored object

            /**
             * \brief assessor operator to the stored object
             **/
            T* operator->();

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            T& operator*();

            /**
             * \brief Copy operator
             **/
            FKBase<T>& operator=(const FKBase<T>& other);

            /**
             * \brief Copy operator
             **/
            FKBase<T>& operator=(const typename Cache<T>::type_ptr& other);

        protected:
            /**
             * \brief Construct a FK
             *
             * \param column Column where the object fk is stored
             * \param nullable if the fk can be null
             **/
            FKBase(const std::string& column,const bool nullable=true);

            std::shared_ptr<T> value_ptr; ///< the stored object

            /**
             * \brief Print the object
             **/
            virtual void print(std::ostream& output) const;

            /**
             * \brief Set the fk value to the query
             *
             * \param query the prepared query
             * \param column the column number of the table
             *
             * \return false if fail
             **/
            virtual bool set(Query& query,const unsigned int& column);

            /**
             * \brief get the fk from the query
             *
             * \param query the executed query
             * \param prefix the column number
             * \param max_depth the maximun recursion of construction
             *
             * \return false if fail
             **/
            virtual bool get(const Query& query,int& prefix,int max_depth);

            /**
             * \brief Construct a new object from the bdd
             *
             * \param bdd the bdd to fetch
             * \param max_depth maximun depth of construction
             *
             * \return The new object
             **/
            T* getObjectT_ptr(Bdd& bdd,int max_depth = ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief make the attrs colum name
             *
             * \param bdd bdd use for the query
             * \param prefix prefix table alias for linked object
             * \param max_depth maximun depth of construction
             *
             * \return the columns alias
             **/
            virtual std::string makeName(Bdd& bdd,const std::string& prefix,int max_depth) const;

            /**
             * \brief Use for increment the column number without construction.
             * Note : this is use with the cache if the object is find in it
             *
             * \param depth column nuber to increment
             * \param max_depth maximun depth of construction
             **/
            virtual void incDepth(int& depth,int max_depth) const;

            /**
             * \brief get the stored object
             *
             * \param bdd the bdd to fetch
             * \param max_depth maximun depth of construction if object not existe
             *
             * \return the stored object
             **/
            virtual const SQLObjectBase& getObject(Bdd& bdd,int max_depth=ORM_DEFAULT_MAX_DEPTH);

    };
}

#include <ORM/fields/private/FKBase.tpl>

#endif
