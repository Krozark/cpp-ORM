#ifndef ORM_VATTR_HPP
#define ORM_VATTR_HPP

#include <string>
#include <ORM/externals.hpp>

namespace orm
{
    class Query;
    class DB;
    class Sqlite3DB;
    class MySqlDB;
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

            virtual ~VAttr();

            /**
             * \brief print the value
             **/
            friend std::ostream& operator<<(std::ostream& output,const VAttr& self);

            /**
             * \brief use by subclass for change the "<<" display
             * \brief print the value
             **/
            virtual std::ostream& printValue(std::ostream& output)const = 0;

            virtual std::string asString()const = 0;

            /**
             * \brief return the column name
             **/
            const std::string& getColumn() const;

            /**
            * \brief set the internal value from a string
            * \return true on success
            * \note : special Format
            * bool : true, false, or integer
            * date : "%d/%m/%Y %H:%M:%S" (day/mounth/year hour:minutes:secondes)
            */
            virtual bool setValue(const std::string&) = 0;

            /**
             * \brief add the attr to the object
             *
             * \param obj The owner of the attr
             **/
            virtual void registerAttr(SqlObjectBase& obj);

        protected:
            friend class DB;
            friend class Sqlite3DB;
            friend class MySqlDB;

            friend class SqlObjectBase;
            template<typename T> friend class Register;
            template<typename T> friend class SqlObject;

            bool _modified; ///< if the attr as been modify
            const std::string& _column; ///< the column name

            /**
             * \brief prepare the field before save it in DB (new object only)
             * Note : do nothing by default.
             */
            virtual void _beforeSave();

            /**
             * \brief prepare the field after save it in DB (new object only)
             * Note : do nothing by default.
             */
            virtual void _afterSave();

            /**
             * \brief prepare the field before update it in DB (not new object only)
             * Note : do nothing by default.
             */
            virtual void _beforeUpdate();

            /**
             * \brief prepare the field after update it in DB (not new object only)
             * Note : do nothing by default.
             */
            virtual void _afterUpdate();
        private:

            /**
             * \brief set the value to the query
             *
             * \param query the prepared query
             * \param column the column number
             **/
            virtual bool _setToQuery(Query& query,const unsigned int& column) = 0;

            /**
             * \brief Get the value form the query row
             *
             * \param query executed query
             * \param prefix colum number
             * \param max_depth the maximum depth recursion
             *
             * \return false if fail
             **/
            virtual bool _getFromQuery(const Query& query,int& prefix,int max_depth) = 0;


            /**
             * \brief create the attr column
             */
            virtual std::string _create(const DB& db) const = 0;

            /**
             * \brief make the colum alias
             *
             * \param db DB use for the query
             * \param prefix the prefix alias of the object
             * \param max_depth maximun depth construction
             *
             * \return the culumn alias
             **/
            virtual std::string _makeName(DB& db,const std::string& prefix,int max_depth) const;
    };
};

#endif
