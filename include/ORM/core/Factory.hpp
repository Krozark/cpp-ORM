#ifndef ORM_FACTORY_HPP
#define ORM_FACTORY_HPP

#include <string>
#include <unordered_map>
#include <functional>

namespace orm
{
    template<typename T>
    class Factory
    {
        public:
            using Container = std::unordered_map < std::string, std::function<T()> >;

            T create(const std::string& className) const;

            void add(const std::string& className, std::function<T()> constructor);

            typename Container::const_iterator begin() const;

            typename Container::const_iterator end() const;


        private:
            Container _constructors;
    };
}

#include <ORM/core/Factory.tpl>

#endif
