#ifndef ORM_AUTOFIELD_HPP
#define ORM_AUTOFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class AutoField : public Attr<int>
    {
        public:
            AutoField(const int& value,const std::string& column);
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
