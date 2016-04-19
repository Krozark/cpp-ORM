#ifndef ORM_TABLES_HPP
#define ORM_TABLES_HPP

#include <vector>
#include <string>
#include <ORM/core/Factory.hpp>
#include <ORM/models/SqlObjectBase.hpp>

namespace orm
{
    template<typename T> class Register;

    /**
     * \brief class that manage all the referencies tables (class)
     */
    class Tables
    {
        public:

            /**
             * \brief create all the tables
             * \return the number of tables created
             */
            static int create();

            /**
             * \brief drop all the tables
             * \return the number of success
             */
            static int drop();

            /**
             * \brief truncate all the tables
             * \return the number of success
             */
            static int clear();

            /**
            \brief get the internal Factory
            */
            static Factory<SqlObjectBase::pointer>& getFactory();

        private:
            template<typename T> friend class Register;
            template<typename T,typename U> friend class M2MRegister;

            static std::vector<bool(*)()> _create; ///< function ptr on SqlObject<T>::create
            static std::vector<bool(*)()> _drop; ///< function ptr on SqlObject<T>::del
            static std::vector<bool(*)()> _clear; ///<function ptr on SqlObject<T>::clear

            Tables() = delete;
            Tables(const Tables&) = delete;
            Tables(Tables&&) = delete;
    };
}

#endif
