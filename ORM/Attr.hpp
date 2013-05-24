#ifndef ORM_ATTR_HPP
#define ORM_ATTR_HPP

#include <ostream>
#include <utility>

#include "VAttr.hpp"

namespace orm
{
    class Query;

    template<typename T>
    class Attr : public VAttr
    {
        public:
            Attr(const T& value,const std::string& colum);
            Attr(const std::string& colum);

            Attr(const Attr&) = delete;

            virtual bool get(const Query& query);
            typedef T type;
            T value;
            
            template<typename U> T& operator=(const U& v){value=v;return value;};
            Attr<T>& operator=(const Attr<T>& v) {value=v.value;return*this;};
            
            template<typename U> auto operator+(const U& v) -> decltype(value+v) const {return value+v;};
            template<typename U> auto operator-(const U& v) -> decltype(value-v) const {return value-v;};
            template<typename U> auto operator*(const U& v) -> decltype(value*v) const {return value*v;};
            template<typename U> auto operator/(const U& v) -> decltype(value/v) const {return value/v;};
            template<typename U> auto operator%(const U& v) -> decltype(value%v) const {return value%v;};

            Attr<T>& operator++(){++value;return *this;};
            Attr<T>& operator++(int){value++;return*this;};

            Attr<T>& operator--(){--value;return*this;};
            Attr<T>& operator--(int){value--;return*this;};
            
            template<typename U> auto operator==(const U& v) -> decltype(value==v) const {return value==v;};
            template<typename U> auto operator!=(const U& v) -> decltype(value!=v)  const {return value!=v;};
            template<typename U> auto operator>(const U& v) -> decltype(value>v) const {return value>v;};
            template<typename U> auto operator<(const U& v) -> decltype(value<v) const {return value<v;};
            template<typename U> auto operator>=(const U& v) -> decltype(value>=v)  const {return value>=v;};
            template<typename U> auto operator<=(const U& v) -> decltype(value<=v)  const {return value<=v;};

            bool operator!()const {return !value;};

            template<typename U> Attr<T>& operator+=(const U& v) {value+=v;return*this;};
            template<typename U> Attr<T>& operator-=(const U& v) {value-=v;return*this;};
            template<typename U> Attr<T>& operator*=(const U& v) {value*=v;return*this;};
            template<typename U> Attr<T>& operator/=(const U& v) {value/=v;return*this;};
            template<typename U> Attr<T>& operator%=(const U& v) {value%=v;return*this;};

            operator T() {return value;};

            
            T operator+(const Attr<T>& v)const {return value+v.value;};
            T operator-(const Attr<T>& v)const {return value-v.value;};
            T operator*(const Attr<T>& v)const {return value*v.value;};
            T operator/(const Attr<T>& v)const {return value/v.value;};
            T operator%(const Attr<T>& v)const {return value%v.value;};

            template<typename U> bool operator==(const Attr<U>& v)const {return value==v.value;};
            template<typename U> bool operator!=(const Attr<U>& v)const {return value!=v.value;};
            template<typename U> bool operator>(const Attr<U>& v)const {return value>v.value;};
            template<typename U> bool operator<(const Attr<U>& v)const {return value<v.value;};
            template<typename U> bool operator>=(const Attr<U>& v)const {return value>=v.value;};
            template<typename U> bool operator<=(const Attr<U>& v)const {return value<=v.value;};

            template<typename U> Attr<T>& operator+=(const Attr<U>& v) {value+=v.value;return*this;};
            template<typename U> Attr<T>& operator-=(const Attr<U>& v) {value-=v.value;return*this;};
            template<typename U> Attr<T>& operator*=(const Attr<U>& v) {value*=v.value;return*this;};
            template<typename U> Attr<T>& operator/=(const Attr<U>& v) {value/=v.value;return*this;};
            template<typename U> Attr<T>& operator%=(const Attr<U>& v) {value%=v.value;return*this;};

        protected:
            virtual void print(std::ostream& output) const;
            virtual bool set(Query& query,const unsigned int& colum) const;
    };
};
#include "Attr.tpl"
#endif
