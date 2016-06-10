#ifndef ORM_VOBJECTMIXIN_HPP
#define ORM_VOBJECTMIXIN_HPP

#include <string>

namespace orm
{
    class DB;

    class VObjectMixin
    {
        public:

            virtual ~VObjectMixin();

            /**
             * \brief Save or update the object on the fk
             *
             * \param db the db to fetch
             * \param recursive save recursively
             *
             * \return false if fail
             **/
            virtual bool save(bool recursive, DB&) = 0;

            /**
            * \brief Save or update the object on the fk
            * Overload of save()
            *
            * \param recursive save recursively
            *
            * \return false if fail
            **/
            bool save(bool recursive = false);

            /**
             * \brief Delete the object from the db and cache
             *
             *  Note : whe use on object linked in other object with fks can cause trouble because of the remove of the cache
             *  Set the pk to -1
             *
             * \param db the db to fetch
             *
             * \return fale if fail
             **/
            virtual bool del(bool recursive, DB&) = 0;

            /**
            * \brief Delete the object from the db and cache
            * overload of del()
            *
            *  Note : whe use on object linked in other object with fks can cause trouble because of the remove of the cache
            *  Set the pk to -1
            *
            * \return fale if fail
            **/
            bool del(bool recursive = false);


            /**
            \brief return the default database registred for the object
            */
            virtual DB& getDefaultDataBase()const = 0;

            /**
            * \return the table name
            **/
            virtual const std::string& getTable() const = 0;


        protected:

        private:
    };
}
#endif
