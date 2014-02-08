#ifndef ORM_VATTR_HPP
#define ORM_VATTR_HPP

#include <string>
#include <ORM/externals.hpp>

namespace orm
{
    class Query;
    class Bdd;
    class Sqlite3Bdd;
    class MySqlBdd;
    class SqlObjectBase;
    template<typename T> class Register;

    /**
     * \brief base class of all attribute stored in data base
     **/
    class VAttr
    {
        public:
            /***
             * \brief Construct a attribute
             *
             * \param column the column name of the table value
             **/
            VAttr(const std::string& column);

            VAttr(const VAttr&) = delete;
            VAttr& operator=(const VAttr&) = delete;

            /**
             * \brief print the value
             **/
            friend std::ostream& operator<<(std::ostream& output,const VAttr& self);

            /**
             * \brief print the value
             **/
            virtual std::ostream& print_value(std::ostream& output)const = 0;

            /**
             * \brief return the column name
             **/
            const std::string& getcolumn() const;

            /**
             * \brief add the attr to the object
             *
             * \param obj The owner of the attr
             **/
            virtual void registerAttr(SqlObjectBase& obj);

        protected:
            friend class Bdd;
            friend class Sqlite3Bdd;
            friend class MySqlBdd;

            friend class SqlObjectBase;
            template<typename T> friend class Register;
            template<typename T> friend class SqlObject;

            bool modify; ///< if the attr as been modify
            const std::string& column; ///< the column name

            /**
             * \brief use by subclass for change the "<<" display
             *
             * \param output Wher to display the content
             **/
            virtual void print(std::ostream& output) const =0;

            /**
             * \brief set the value to the query
             *
             * \param query the prepared query
             * \param column the column number
             **/
            virtual bool set(Query& query,const unsigned int& column) = 0;

            /**
             * \brief Get the value form the query row
             *
             * \param query executed query
             * \param prefix colum number
             * \param max_depth the maximum depth recursion
             *
             * \return false if fail
             **/
            virtual bool get(const Query& query,int& prefix,int max_depth) = 0;

            /**
             * \brief make the colum alias
             *
             * \param bdd Bdd use for the query
             * \param prefix the prefix alias of the object
             * \param max_depth maximun depth construction
             *
             * \return the culumn alias
             **/
            virtual std::string makeName(Bdd& bdd,const std::string& prefix,int max_depth) const;

            /**
             * \brief create the attr column
             */
            virtual std::string create(const Bdd& bdd) const = 0;
    };
};

#endif
