#ifndef ORM_FK_HPP
#define ORM_FK_HPP

#include <ORM/fields/VFK.hpp>

namespace orm
{
    class Query;

    template<typename T>
    class FK : public VFK
    {
        public:
            FK(const int& id,const std::string& colum);//TODO ++on cache counter
            FK(const std::string& colum);//TODO idem
            FK(const FK&) = delete;

            ~FK(); //TODO --on cache counter

            virtual const SQLObjectBase& getObject()const;

            typedef T type;

            T& operator*(){return *value_ptr;};
            T* operator->(){return value_ptr;};

            FK<T>& operator=(const FK<T>& other);

        protected:
            T* value_ptr;

            virtual void print(std::ostream& output) const;
            virtual bool set(Query& query,const unsigned int& colum) const;
            virtual bool get(const std::string& prefix,const Query& query);

    };
}

#include <ORM/fields/FK.tpl>

#endif
