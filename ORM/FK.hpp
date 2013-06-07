#ifndef ORM_FK_HPP
#define ORM_FK_HPP

#include "VFK.hpp"

namespace orm
{
    class Query;

    template<typename T>
    class FK : public VFK
    {
        public:
            FK(const int& id,const std::string& colum);//TODO ++on cash counter
            FK(const std::string& colum);//TODO idem
            FK(const FK&) = delete;

            ~FK(); //TODO --on cash counter

            virtual const SQLObjectBase& getObject()const;

            virtual bool get(const Query& query);
            typedef T type;

            T& operator*(){return *value_ptr;};
            T* operator->(){return value_ptr;};

            FK<T>& operator=(const FK<T>& other);

        protected:
            T* value_ptr;

            virtual void print(std::ostream& output) const;
            virtual bool set(Query& query,const unsigned int& colum) const;

    };
}

#include "FK.tpl"

#endif
