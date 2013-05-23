#ifndef ORM_VATTR_HPP
#define ORM_VATTR_HPP

#include <string>

namespace orm
{
    class Query;

    class VAttr
    {
        public:
            VAttr(const std::string& colum);
            virtual bool get(const Query& query) = 0;
            friend std::ostream& operator<<(std::ostream& output,const VAttr& self)
            {
                self.print(output);
                return output;
            };
        protected:
            const std::string& colum;
            //bool modify;
            virtual void print(std::ostream& output) const =0;
    };
};

#endif
