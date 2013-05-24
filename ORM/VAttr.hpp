#ifndef ORM_VATTR_HPP
#define ORM_VATTR_HPP

#include <string>
#include "debug.hpp"

namespace orm
{
    class Query;
    class Bdd;

    class VAttr
    {
        public:
            VAttr(const std::string& colum);

            VAttr(const VAttr&) = delete;
            VAttr& operator=(const VAttr&) = delete;

            virtual bool get(const Query& query) = 0;
            friend std::ostream& operator<<(std::ostream& output,const VAttr& self);

        protected:
            friend class Bdd;
            bool modify;
            const std::string& colum;
            virtual void print(std::ostream& output) const =0;
            virtual bool set(Query& query,const unsigned int& colum) const = 0;
    };
};

#endif
