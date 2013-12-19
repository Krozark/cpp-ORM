#ifndef ORM_ATTR_HPP
#define ORM_ATTR_HPP

#include <ostream>
#include <utility>
#include <string>

#include <ORM/fields/private/VAttr.hpp>

namespace orm
{
    class Query;

    /**
     * \brief Store a value ass database row
     **/
    template<typename T>
    class Attr : public VAttr
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in bdd
             **/
            Attr(const T& value,const std::string& column);

            /**
             * \brief Make a Attr
             *
             * \param column Column in bdd
             **/
            Attr(const std::string& column);

            Attr(const Attr&) = delete;

            typedef T type; ///< type of stored object
            T value; ///< value stored
            
            /**
             * \brief assignement operator
             *
             * \param v value to copy
             *
             * \return value
             **/
            template<typename U> T& operator=(const U& v){value=v;modify=true;return value;};

            /**
             * \brief assignement operator
             *
             * \param v value to copy
             *
             * \return *this
             **/
            Attr<T>& operator=(const Attr<T>& v) {value=v.value;modify=true;return*this;};
            
            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return value+v
             **/
            template<typename U> auto operator+(const U& v) -> decltype(value+v) const {return value+v;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return value-v
             **/
            template<typename U> auto operator-(const U& v) -> decltype(value-v) const {return value-v;};

            /**
             * \brief  multiply operator
             *
             * \param v value to multiply by
             *
             * \return value*v
             **/
            template<typename U> auto operator*(const U& v) -> decltype(value*v) const {return value*v;};

            /**
             * \brief div operator
             *
             * \param v value to div by
             *
             * \return value/v
             **/
            template<typename U> auto operator/(const U& v) -> decltype(value/v) const {return value/v;};

            /**
             * \brief mod operator
             *
             * \param v value to mod by
             *
             * \return v%value
             **/
            template<typename U> auto operator%(const U& v) -> decltype(value%v) const {return value%v;};

            /**
             * \brief post increment operator
             *
             * \return *this
             **/
            Attr<T>& operator++(){++value;modify=true;return *this;};

            /**
             * \brief pre increment operator
             *
             * \return *this
             **/
            Attr<T>& operator++(int){value++;modify=true;return*this;};

            /**
             * \brief post deincrement operator
             *
             * \return *this
             **/
            Attr<T>& operator--(){--value;modify=true;return*this;};

            /**
             * \brief pre deincrement operator
             *
             * \return *this
             **/
            Attr<T>& operator--(int){value--;modify=true;return*this;};
            
            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value == v
             **/
            template<typename U> auto operator==(const U& v) -> decltype(value==v) const {return value==v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value != v
             **/
            template<typename U> auto operator!=(const U& v) -> decltype(value!=v)  const {return value!=v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value > v
             **/
            template<typename U> auto operator>(const U& v) -> decltype(value>v) const {return value>v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value < v
             **/
            template<typename U> auto operator<(const U& v) -> decltype(value<v) const {return value<v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value >= v
             **/
            template<typename U> auto operator>=(const U& v) -> decltype(value>=v)  const {return value>=v;};
            
            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value <= v
             **/
            template<typename U> auto operator<=(const U& v) -> decltype(value<=v)  const {return value<=v;};

            /**
             * \brief negation operator
             *
             * \return !value
             **/
            bool operator!()const {return !value;};


            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator+=(const U& v) {value+=v;modify=true;return*this;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator-=(const U& v) {value-=v;modify=true;return*this;};

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator*=(const U& v) {value*=v;modify=true;return*this;};

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator/=(const U& v) {value/=v;modify=true;return*this;};
            
            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator%=(const U& v) {value%=v;modify=true;return*this;};

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            //operator T() {return value;};

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            operator T()const {return value;};
            
            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return value+v.value
             **/
            T operator+(const Attr<T>& v) const {return value+v.value;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return value-v.value
             **/
            T operator-(const Attr<T>& v) const {return value-v.value;};

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return value*v.value
             **/
            T operator*(const Attr<T>& v) const {return value*v.value;};

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return value/v.value
             **/
            T operator/(const Attr<T>& v) const {return value/v.value;};

            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return value%v.value
             **/
            T operator%(const Attr<T>& v) const {return value%v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value == v.value
             **/
            template<typename U> bool operator==(const Attr<U>& v)const {return value==v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value != v.value
             **/
            template<typename U> bool operator!=(const Attr<U>& v)const {return value!=v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value > v.value
             **/
            template<typename U> bool operator>(const Attr<U>& v)const {return value>v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value < v.value
             **/
            template<typename U> bool operator<(const Attr<U>& v)const {return value<v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value >= v.value
             **/
            template<typename U> bool operator>=(const Attr<U>& v)const {return value>=v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value <= v.value
             **/
            template<typename U> bool operator<=(const Attr<U>& v)const {return value<=v.value;};

            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator+=(const Attr<U>& v) {value+=v.value;modify=true;return*this;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator-=(const Attr<U>& v) {value-=v.value;modify=true;return*this;};

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator*=(const Attr<U>& v) {value*=v.value;modify=true;return*this;};

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator/=(const Attr<U>& v) {value/=v.value;modify=true;return*this;};

            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator%=(const Attr<U>& v) {value%=v.value;modify=true;return*this;};

            /**
             * \brief print the stored value
             *
             * \param output print in this stream
             *
             * \return output
             **/
            virtual std::ostream& print_value(std::ostream& output)const;

        protected:
            /**
             * \brief print the stored value
             *
             * \param output print in this stream
             **/
            virtual void print(std::ostream& output) const;

            /**
             * \brief Set the value in the query (use for dispatch
             *
             * \param query Query to set in
             * \param column culum number to set
             *
             * \return false if fail
             */
            virtual bool set(Query& query,const unsigned int& column);

            /**
             * \brief Extracte the value from the query row
             *
             * \param query executed query
             * \param prefix column number to get
             * \param max_depth max depth of construction recurtion
             *
             * \return false if fail
             **/
            virtual bool get(const Query& query,int& prefix,int max_depth);
    };

    // define more common type
    using IntegerField = Attr<int>;
    using BooleanField = Attr<bool>;
    using PositiveIntegerField = Attr<unsigned int>;
    using BigIntegerField = Attr<long long int>;
    using FloatField = Attr<float>;
    using DoubleField = Attr<double>; ///\todo quesry.set(double,colum)
    using BigDoubleField = Attr<long double>;
    using TextField = Attr<std::string>;

    template<size_t max_length>
    using CharField = Attr<std::string>;


    /*template<bool auto_increment>
    using AutoField = Attr<int>;*/

};
#include <ORM/fields/Attr.tpl>

#endif
