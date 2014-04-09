#ifndef ORM_AUTOFIELD_HPP
#define ORM_AUTOFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    /**
     * \brief This class hade to be use only internaly
     * \todo make it as not internaly
     */
    class AutoField : public Attr<int>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in bdd
             **/
            AutoField(const int& value,const std::string& column);

            /**
             * \brief Make a Attr
             *  default value is -1.
             * \param column Column in bdd
             * 
             **/
            AutoField(const std::string& column);

            AutoField(const AutoField&) = delete;
            AutoField& operator=(const AutoField&) = delete;
            
            using Attr<int>::operator=;

            using Attr<int>::operator==;
            using Attr<int>::operator!=;
            using Attr<int>::operator>;
            using Attr<int>::operator<;
            using Attr<int>::operator>=;
            using Attr<int>::operator<=;

            using Attr<int>::operator!;

            using Attr<int>::operator int;

        protected:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const Bdd& bdd) const;

    };
}
#endif
