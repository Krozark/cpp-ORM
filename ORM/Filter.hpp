#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <string>

namespace orm
{
    class Filter
    {
        public:
            Filter(const std::string& colum,const std::string& ope, const std::string& value);

        private:
            std::string colum;
            const std::string ope;
            const std::string& value;
    };
};

#endif
