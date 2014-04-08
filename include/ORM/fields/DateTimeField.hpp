#ifndef ORM_DATETIMEFIELD_HPP
#define ORM_DATETIMEFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class DateTimeField : public Attr<std::string>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in bdd
             **/
            DateTimeField(const std::string& value,const std::string& column);
            
            /**
             * \brief Make a Attr
             * default value is empty string.
             * \param column Column in bdd
             **/
            DateTimeField(const std::string& column);

            DateTimeField(const DateTimeField&) = delete;
            DateTimeField& operator=(const DateTimeField&) = delete;

            DateTimeField(DateTimeField&&) = default;
            DateTimeField& operator=(DateTimeField&&) = default;

            /*using Attr<std::string>::operator=;

            using Attr<std::string>::operator+;

            using Attr<std::string>::operator==;
            using Attr<std::string>::operator!=;
            using Attr<std::string>::operator>;
            using Attr<std::string>::operator<;
            using Attr<std::string>::operator>=;
            using Attr<std::string>::operator<=;

            using Attr<std::string>::operator+=;*/
            using Attr<std::string>::operator std::string;
            
            static DateTimeField now();

        protected:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const Bdd& bdd) const;
    };
}
#endif
