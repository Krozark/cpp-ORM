#ifndef ORM_BOOLEANFIELD_HPP
#define ORM_BOOLEANFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class BooleanField : public Attr<bool>
    {
        public:
            BooleanField(const bool& value,const std::string& column);
            BooleanField(const BooleanField&) = delete;
            BooleanField& operator=(const BooleanField&) = delete;

            using Attr<bool>::operator=;

            using Attr<bool>::operator+;
            using Attr<bool>::operator-;
            using Attr<bool>::operator*;
            using Attr<bool>::operator/;

            using Attr<bool>::operator==;
            using Attr<bool>::operator!=;
            using Attr<bool>::operator>;
            using Attr<bool>::operator<;
            using Attr<bool>::operator>=;
            using Attr<bool>::operator<=;

            using Attr<bool>::operator!;

            using Attr<bool>::operator+=;
            using Attr<bool>::operator-=;
            using Attr<bool>::operator bool;

        protected:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const Bdd& bdd) const;
    };
}
#endif
