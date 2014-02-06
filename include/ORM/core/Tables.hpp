#ifndef ORM_TABLES_HPP
#define ORM_TABLES_HPP

#include <vector>

namespace orm
{
    template<typename T> class Register;

    class Tables
    {
        public:

            static bool create();
            static bool drop();
            static bool truncate();

        private:
            template<typename T> friend class Register;

            static std::vector<bool(*)()> _create;
            static std::vector<bool(*)()> _drop;
            static std::vector<bool(*)()> _truncate;

            Tables() = delete;
            Tables(const Tables&) = delete;
            Tables(Tables&&) = delete;
    };
}

#endif
