#ifndef ORM_INTEGERFIELD_HPP
#define ORM_INTEGERFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class IntegerField : public Attr<int>
    {
        public:
            IntegerField(const int& value,const std::string& column);
            IntegerField(const IntegerField&) = delete;
            IntegerField& operator=(const IntegerField&) = delete;

            using Attr<int>::operator=;

            using Attr<int>::operator+;
            using Attr<int>::operator-;
            using Attr<int>::operator*;
            using Attr<int>::operator/;
            using Attr<int>::operator%;

            using Attr<int>::operator++;
            using Attr<int>::operator--;

            using Attr<int>::operator==;
            using Attr<int>::operator!=;
            using Attr<int>::operator>;
            using Attr<int>::operator<;
            using Attr<int>::operator>=;
            using Attr<int>::operator<=;

            using Attr<int>::operator!;

            using Attr<int>::operator+=;
            using Attr<int>::operator-=;
            using Attr<int>::operator*=;
            using Attr<int>::operator/=;
            using Attr<int>::operator%=;
            using Attr<int>::operator int;

        protected:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const Bdd& bdd) const;
    };
}
#endif
