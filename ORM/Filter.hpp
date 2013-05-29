#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <string>

namespace orm
{
    template<typename T> class SQLObject;
    class Filter
    {
        public:
            Filter(const std::string& colum,const std::string& ope, const std::string& value);

        private:
            template<typename T> friend class SQLObject;
            std::string colum;
            const std::string ope;
            const std::string value;
    };
};

#endif
