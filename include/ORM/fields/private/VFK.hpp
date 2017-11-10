#ifndef ORM_VFK_HPP
#define ORM_VFK_HPP

#include <ORM/core/VObjectMixin.hpp>
#include <ORM/fields/private/VAttr.hpp>
#include <ORM/models/SqlObjectBase.hpp>


namespace orm
{
    template<typename T> class SqlObject;

    /**
     * \brief base classe of all FK stored in database
     **/
    class VFK : public VAttr , public VObjectMixin
    {
        public:
            /**
             * \brief Construct a FK
             *
             * \param column Column where the object fk is stored
             * \param nullable if the fk can be null
             **/
            VFK(const std::string& column,const bool nullable=true);

            /**
             * \brief add the attr to the object
             *
             * \param obj The owner of the attr
             **/
            virtual void registerAttr(SqlObjectBase&) final;


            /**
             * \return the fk value
             */
            int getFk()const;

            virtual bool test() const = 0;

            /**
            * \brief set the internal value from a string
            * \return true on success
            */
            virtual bool setValue(const std::string&) override;


            /**
            * \brief set the internal value from a string
            * \return true on success
            */
            virtual bool setValue(SqlObjectBase::pointer& ptr) = 0;


            virtual std::string asString()const override;

        protected:
            template<typename T> friend class SqlObject;

            int _fk; ///< the fk value (if fk <=0 => null)
            //bool loaded; ///< as a loaded object
            const bool _nullable; ///< is nullable

            /**
             * \brief Use for increment the column number without construction.
             * Note : this is use with the cache if the object is find in it
             *
             * \param depth column nuber to increment
             * \param max_depth maximun depth of construction
             **/
            virtual void _incDepth(int& depth,int max_depth)const = 0;

            /**
             * \brief get the stored object
             *
             * \param db the db to fetch
             * \param max_depth maximun depth of construction if object not existe
             *
             * \return the stored object
             **/
            virtual const SqlObjectBase& _getObject(DB& db,int max_depth=ORM_DEFAULT_MAX_DEPTH)= 0;



    };
}
#endif
