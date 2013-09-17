#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <string>

namespace orm
{
    template<typename T> class SQLObject;
    class Filter
    {
        public:
            template<typename T>
            Filter(const std::string& colum,const std::string& ope, const T& value);
            
            void __print__() const;

        private:
            template<typename T> friend class SQLObject;
            const std::string colum;
            const std::string ope;
            const std::string value;
    };
};

#include <ORM/backends/Filter.tpl>

#endif
