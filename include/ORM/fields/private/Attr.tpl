#include <ORM/backends/Query.hpp>

#include <ORM/core/from_string.hpp>
#include <typeinfo>
#include <sstream>

namespace orm
{
    template<typename T>
    Attr<T>::Attr(const T& val,const std::string& col) : VAttr(col), _value(val), _prepared(false)
    {
    };

    template<typename T>
    Attr<T>::Attr(const std::string& col) : VAttr(col) , _value(), _prepared(false)
    {
    };

    template<typename T>
    bool Attr<T>::setValue(const std::string& value)
    {
        T tmp;
        if (from_string<T>(value, tmp))
        {
            _setValue(tmp);
            return true;
        }
        return false;
    }

    template<typename T>
    bool Attr<T>::_getFromQuery(const Query& query,int& prefix,int max_depth)
    {
        _prepared = false;
        return query._get(_value,prefix);
    };

    template<typename T>
    T Attr<T>::_prepareToDb(const T& value)
    {
        return value;
    }

    template<typename T>
    bool Attr<T>::_setToQuery(Query& query,const unsigned int& column)
    {
        bool res;

        if(_prepared)//_value is for local
        {
            T tmp = _prepareToDb(_value);
            res = query._set(tmp,column);
        }
        else
        {
            res = query._set(_value,column);
        }
        return res;
    };

    template<typename T>
    T Attr<T>::_prepareFromDb(const T& value)
    {
        return value;
    }


    template<typename T>
    std::ostream& Attr<T>::printValue(std::ostream& output)const
    {
        return (output<<'"'<<_value<<'"');
    }

    template<typename T>
    std::string Attr<T>::asString()const
    {
        std::stringstream ss;
        ss << _value;
        return ss.str();
    }

    template<typename T>
    const T& Attr<T>::getValue()const
    {
        return _value;
    }


    template<typename T>
    T& Attr<T>::_getValue()
    {
        if(not _prepared)
        {
            _value = _prepareFromDb(_value);
            _prepared = true;
        }
        return _value;
    }

    template<typename T>
    void Attr<T>::_setValue(const T& v)
    {
        _prepared = true;
        _modified = true;
        _value = v;
    }

    template<typename T>
    template<typename U>
    T& Attr<T>::operator=(const U& v)
    {
        _setValue(v);
        return _value;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator=(const Attr<T>& v)
    {
        _setValue(v._value);
        _prepared = v._prepared;
        _value=v._value;
        return*this;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator+(const U& v) -> decltype(_value+v)
    {
        return _getValue()+v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator-(const U& v) -> decltype(_value-v)
    {
        return _getValue()-v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator*(const U& v) -> decltype(_value*v)
    {
        return _getValue()*v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator/(const U& v) -> decltype(_value/v)
    {
        return _getValue()/v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator%(const U& v) -> decltype(_value%v)
    {
       return _getValue()%v;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator++()
    {
        _getValue();
        ++_value;
        _modified=true;
        return *this;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator++(int)
    {
        _getValue();
        ++_value;
        _modified=true;
        return *this;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator--()
    {
        _getValue();
        --_value;
        _modified=true;
        return *this;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator--(int)
    {
        _getValue();
        --_value;
        _modified=true;
        return *this;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator==(const U& v)
    {
        return _getValue() == v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator!=(const U& v)
    {
        return _getValue()!=v;
    }

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>(const U& v)
    {
        return _getValue()>v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<(const U& v)
    {
        return _getValue()<v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>=(const U& v)
    {
        return _getValue()>=v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<=(const U& v)
    {
        return _getValue()<=v;
    };

    template<typename T>
    bool Attr<T>::operator!()
    {
        return !_getValue();
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator+=(const U& v)
    {
        _getValue()+=v;
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator-=(const U& v)
    {
        _getValue()-=v;
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator*=(const U& v)
    {
        _getValue()*=v;
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator/=(const U& v)
    {
        _getValue()/=v;
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator%=(const U& v)
    {
        _getValue()%=v;
        _modified=true;
        return*this;
    };

    template<typename T>
    Attr<T>::operator T()
    {
        return _getValue();
    };

    template<typename T>
    T Attr<T>::operator+(Attr<T>& v)
    {
        return _getValue()+v._getValue();
    };

    template<typename T>
    T Attr<T>::operator-(Attr<T>& v)
    {
        return _getValue()-v._getValue();
    };

    template<typename T>
    T Attr<T>::operator*(Attr<T>& v)
    {
        return _getValue()*v._getValue();
    };

    template<typename T>
    T Attr<T>::operator/(Attr<T>& v)
    {
        return _getValue()/v._getValue();
    };

    template<typename T>
    T Attr<T>::operator%(Attr<T>& v)
    {
        return _getValue()%v._getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator==(Attr<U>& v)
    {
        return _getValue()==v._getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator!=(Attr<U>& v)
    {
        return _getValue()!=v._getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>(Attr<U>& v)
    {
        return _getValue()>v._getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<(Attr<U>& v)
    {
        return _getValue()<v._getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>=(Attr<U>& v)
    {
        return _getValue()>=v._getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<=(Attr<U>& v)
    {
        return _getValue()<=v._getValue();
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator+=(Attr<U>& v)
    {
        _getValue()+=v._getValue();
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator-=(Attr<U>& v)
    {
        _getValue()-=v._getValue();
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator*=(Attr<U>& v)
    {
        _getValue()*=v._getValue();
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator/=(Attr<U>& v)
    {
        _getValue()/=v._getValue();
        _modified=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator%=(Attr<U>& v)
    {
        _getValue()%=v._getValue();
        _modified=true;
        return*this;
    };
};
