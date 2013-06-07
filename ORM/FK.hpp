#ifndef ORM_FK_HPP
#define ORM_FK_HPP

#include "VAttr.hpp"

namespace orm
{
    class Query;

    template<typename T>
    class FK : public VAttr
    {
        FK(const int& id,const std::string& colum);//TODO ++on cash counter
        FK(const std::string& colum);//TODO idem

        ~FK(); //TODO --on cash counter

        FK(const FK&) = delete;

        virtual bool get(const Query& query);
        typedef T type;

        T& operator*(){return *value_ptr;};
        T* operator->(){return value_ptr;};

        protected:
            int value;
            T* value_prt;

            virtual void print(std::ostream& output) const;
            virtual bool set(Query& query,const unsigned int& colum) const;

    };
}

#endif
