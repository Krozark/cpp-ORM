#ifndef ORM_ATTR_HPP
#define ORM_ATTR_HPP

#include <ostream>

#include "VAttr.hpp"

namespace orm
{
    class Query;

    template<typename T>
    class Attr : public VAttr
    {
        public:
            Attr(const T& value,const std::string colum);

            virtual bool get(const Query& query);
            typedef T type;
            T value;
        protected:
            virtual void print(std::ostream& output) const;
    };
};
#include "Attr.tpl"
#endif
