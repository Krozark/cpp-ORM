#include <ORM/fields/DateTimeField.hpp>
#include <cstring>
#include <cstdio>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    DateTimeField::DateTimeField(const struct tm& value,const std::string& column) : Attr(value,column)
    {
    }

    DateTimeField::DateTimeField(const std::string& column) : Attr(tm{0},column)
    {
    }

    int& DateTimeField::year()
    {
        return _value.tm_year;
    }

    int DateTimeField::year()const
    {
        return _value.tm_year;
    }

    int& DateTimeField::month()
    {
        return _value.tm_mon;
    }

    int DateTimeField::month()const
    {
        return _value.tm_mon;
    }

    int& DateTimeField::day()
    {
        return _value.tm_mday;
    }

    int DateTimeField::day()const
    {
        return _value.tm_mday;
    }

    int& DateTimeField::hour()
    {
        return _value.tm_hour;
    }

    int DateTimeField::hour()const
    {
        return _value.tm_hour;
    }

    int& DateTimeField::minute()
    {
        return _value.tm_min;
    }

    int DateTimeField::minute()const
    {
        return _value.tm_min;
    }

    int& DateTimeField::second()
    {
        return _value.tm_sec;
    }

    int DateTimeField::second()const
    {
        return _value.tm_sec;
    }

    int& DateTimeField::yday()
    {
        return _value.tm_yday;
    }

    int DateTimeField::yday()const
    {
        return _value.tm_yday;
    }

    std::time_t DateTimeField::as_timestamp()
    {
        return ::mktime(&_value);
    }

    /*DateTimeField& DateTimeField::operator>(const DateTimeField& other)
    {
        return *this > other._value;
    }

    DateTimeField& DateTimeField::operator>=(const DateTimeField& other)
    {
        return *this >= other._value;
    }

    DateTimeField& DateTimeField::operator<(const DateTimeField& other)
    {
        return *this < other._value;
    }

    DateTimeField& DateTimeField::operator<=(const DateTimeField& other)
    {
        return *this <= other._value;
    }

    DateTimeField& DateTimeField::operator==(const DateTimeField& other)
    {
        return *this == other._value;
    }

    DateTimeField& DateTimeField::operator+(const DateTimeField& other)
    {
        return *this + other._value;
    }

    DateTimeField& DateTimeField::operator-(const DateTimeField& other)
    {
        return *this - other._value;
    }*/


    bool DateTimeField::operator>(const struct tm& other)
    {
        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        return as_timestamp() > ::mktime(&tmp);
    }

    bool DateTimeField::operator>=(const struct tm& other)
    {
        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        return as_timestamp() >= ::mktime(&tmp);
    }

    bool DateTimeField::operator<(const struct tm& other)
    {
        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        return as_timestamp() < ::mktime(&tmp);
    }

    bool DateTimeField::operator<=(const struct tm& other)
    {
        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        return as_timestamp() <= ::mktime(&tmp);
    }

    bool DateTimeField::operator==(const struct tm& other)
    {
        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        return as_timestamp() == ::mktime(&tmp);
    }

    struct tm DateTimeField::operator+(const struct tm& other)
    {

        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        std::time_t res = as_timestamp() + ::mktime(&tmp);
        ::gmtime_r(&res,&tmp);
        return tmp;
    }

    struct tm DateTimeField::operator-(const struct tm& other)
    {
        struct tm tmp;
        ::memcpy(&tmp,&other,sizeof(struct tm));
        std::time_t res = as_timestamp() - ::mktime(&tmp);
        ::gmtime_r(&res,&tmp);
        return tmp;
    }

    struct tm DateTimeField::now()
    {
        struct tm tmp;
        std::time_t t = ::time(nullptr);
        ::gmtime_r(&t,&tmp);
        tmp.tm_year +=1900;
        tmp.tm_mon +=1;
        ::mktime(&tmp);
        return tmp;
    }

    struct tm DateTimeField::prepare_to_db(const struct tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(struct tm));
        tmp.tm_year +=1900;
        tmp.tm_mon +=1;
        ::mktime(&tmp);
        return tmp;
    }

    struct tm DateTimeField::prepare_from_db(const struct tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(struct tm));
        tmp.tm_year -=1900;
        tmp.tm_mon -=1;
        tmp.tm_isdst = -1;
        ::mktime(&tmp);
        return tmp;
    }

    std::string DateTimeField::create(const DB& db) const
    {
        return db.creator().dateTimeField(column,false);
    }
}

#include <iomanip>
std::ostream& operator<<(std::ostream& stream,const struct tm& time)
{
    char prev = stream.fill ('x');
    stream<<std::setfill('0')
        <<std::setw(4)<<time.tm_year<<"-"<<std::setw(2)<<time.tm_mon<<"-"<<std::setw(2)<<time.tm_mday<<" "
        <<std::setw(2)<<time.tm_hour<<":"<<std::setw(2)<<time.tm_min<<":"<<std::setw(2)<<time.tm_sec
        <<std::setw(0)<<std::setfill(prev);
    return stream;
}

