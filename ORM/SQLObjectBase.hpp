#ifndef ORM_SQLOBJECTBASE_HPP
#define ORM_SQLOBJECTBASE_HPP

#include <vector>
#include <ostream>

#include "debug.hpp"

namespace orm
{
    class Bdd;
    class Query;
    class VAttr;

    class SQLObjectBase
    {
        public:
            SQLObjectBase();

            SQLObjectBase(const SQLObjectBase&)=delete;
            SQLObjectBase& operator=(const SQLObjectBase&)=delete;

            bool loadFromBdd(const Query& query);
            virtual bool save(bool _new=false) = 0;

            friend std::ostream& operator<<(std::ostream& output,const SQLObjectBase& self);

        protected:
            int pk;
            std::vector<VAttr*> attrs;

            void registerAttr(VAttr& attr);
    };
};


#endif
