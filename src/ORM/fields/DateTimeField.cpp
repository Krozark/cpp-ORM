#include <ORM/fields/DateTimeField.hpp>
#include <ORM/backends/private/TableCreator.hpp>

#include <cstring>
#include <cstdio>
#include <iomanip>

namespace orm
{

    DateTimeField::DateTimeField(const tm& value,const std::string& column) : Attr(value,column)
    {
    }

    DateTimeField::DateTimeField(const std::string& column) : Attr(tm{0},column)
    {
    }

    int& DateTimeField::year()
    {
        return _getValue().tm_year;
    }

    int& DateTimeField::month()
    {
        return _getValue().tm_mon;
    }

    int& DateTimeField::day()
    {
        return _getValue().tm_mday;
    }

    int& DateTimeField::hour()
    {
        return _getValue().tm_hour;
    }

    int& DateTimeField::minute()
    {
        return _getValue().tm_min;
    }

    int& DateTimeField::second()
    {
        return _getValue().tm_sec;
    }

    int& DateTimeField::yday()
    {
        return _getValue().tm_yday;
    }

    std::time_t DateTimeField::mktime()
    {
        return ::mktime(&_getValue());
    }

    std::ostream& DateTimeField::printValue(std::ostream& stream) const
    {
        char prev = stream.fill ('x');
        return(stream<<'"'
        <<std::setfill('0')
        <<std::setw(4)<<(_value.tm_year+(_prepared?1900:0))
        <<"-"<<std::setw(2)<<(_value.tm_mon+(_prepared?1:0))
        <<"-"<<std::setw(2)<<_value.tm_mday<<" "
        <<std::setw(2)<<_value.tm_hour<<":"<<std::setw(2)<<_value.tm_min<<":"<<std::setw(2)<<_value.tm_sec
        <<std::setw(0)<<std::setfill(prev)
        <<'"');
    };


    tm& DateTimeField::operator=(const tm& other)
    {
        _modified = true;
        _prepared = true;
        ::memcpy(&_value,&other,sizeof(tm));
        return _value;
    }


    tm DateTimeField::now()
    {
        tm * timeinfo;
        time_t rawtime;

        std::time(&rawtime);
        timeinfo = std::localtime(&rawtime);

        timeinfo->tm_isdst = -1;
        return *timeinfo;
    }

    tm DateTimeField::time(int hour,int min,int sec)
    {
        tm tmp{0};
        tmp.tm_year = 0;
        tmp.tm_mon = 0;
        tmp.tm_mday = 0;

        tmp.tm_hour = hour;
        tmp.tm_min = min;
        tmp.tm_sec = sec;
        tmp.tm_isdst = -1;
        return tmp;
    }

    tm DateTimeField::date(int year,int month,int day)
    {
        tm tmp{0};
        tmp.tm_year = year - 1900;
        tmp.tm_mon = month - 1;
        tmp.tm_mday = day;
        tmp.tm_isdst = -1;
        return tmp;
    }

    tm DateTimeField::day(int nb)
    {
        tm tmp{0};
        tmp.tm_mday = nb;
        tmp.tm_isdst = -1;
        return tmp;
    }

    tm DateTimeField::month(int nb)
    {
        tm tmp{0};
        tmp.tm_mon = nb - 1;
        tmp.tm_isdst = -1;
        return tmp;
    }

    tm DateTimeField::year(int nb)
    {
        tm tmp{0};
        tmp.tm_year = nb - 1900;
        tmp.tm_isdst = -1;
        return tmp;
    }

    tm& DateTimeField::normalize(tm& time)
    {
        ::mktime(&time);
        return time;
    }

    tm DateTimeField::normalize(tm&& time)
    {
        ::mktime(&time);
        return time;
    }

    tm DateTimeField::_prepareToDb(const tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(tm));
        ::mktime(&tmp);
        tmp.tm_year +=1900;
        tmp.tm_mon +=1;
        tmp.tm_isdst = -1;
        return tmp;
    }

    tm DateTimeField::_prepareFromDb(const tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(tm));
        tmp.tm_year -=1900;
        tmp.tm_mon -=1;
        tmp.tm_isdst = -1;
        ::mktime(&tmp);
        return tmp;
    }

    std::string DateTimeField::_create(const DB& db) const
    {
        return db.creator().dateTimeField(_column,false);
    }

    //////////////////////////AutoDateTimeField/////////////////////
    AutoDateTimeField::AutoDateTimeField(const tm& value, const std::string& column) :
        DateTimeField(value,column)
    {
    }


    AutoDateTimeField::AutoDateTimeField(const std::string& column):
        DateTimeField(column)
    {
    }

    void AutoDateTimeField::_beforeSave()
    {
        *this=DateTimeField::now();
    }

    /////////////////////AutoNowDateTimeField/////////////////////
    AutoNowDateTimeField::AutoNowDateTimeField(const tm& value, const std::string& column):
        DateTimeField(value, column)
    {
    }

    AutoNowDateTimeField::AutoNowDateTimeField(const std::string& column):
        DateTimeField(column)
    {
    }


    void AutoNowDateTimeField::_beforeSave()
    {
        *this=DateTimeField::now();
    }

    void AutoNowDateTimeField::_beforeUpdate()
    {
        *this=DateTimeField::now();
    }
}

std::ostream& operator<<(std::ostream& stream,const tm& time)
{
    char prev = stream.fill ('x');
    stream<<std::setfill('0')
        <<std::setw(4)<<time.tm_year<<"-"<<std::setw(2)<<time.tm_mon<<"-"<<std::setw(2)<<time.tm_mday<<" "
        <<std::setw(2)<<time.tm_hour<<":"<<std::setw(2)<<time.tm_min<<":"<<std::setw(2)<<time.tm_sec
        <<std::setw(0)<<std::setfill(prev);
    return stream;
}

bool operator>(const tm& first,const tm& second)
{
    tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(tm));
    ::memcpy(&_2,&second,sizeof(tm));

    return mktime(&_1) > ::mktime(&_2);
}

bool operator>=(const tm& first,const tm& second)
{
    tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(tm));
    ::memcpy(&_2,&second,sizeof(tm));

    return mktime(&_1) >= ::mktime(&_2);
}

bool operator<(const tm& first,const tm& second)
{
    tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(tm));
    ::memcpy(&_2,&second,sizeof(tm));

    return mktime(&_1) < ::mktime(&_2);
}

bool operator<=(const tm& first,const tm& second)
{
    tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(tm));
    ::memcpy(&_2,&second,sizeof(tm));

    return mktime(&_1) <= ::mktime(&_2);
}

bool operator==(const tm& first,const tm& second)
{
    tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(tm));
    ::memcpy(&_2,&second,sizeof(tm));

    return mktime(&_1) == ::mktime(&_2);
}

tm operator+(const tm& first,const tm& second)
{
    tm tmp;
    ::memcpy(&tmp,&first,sizeof(tm));
    tmp.tm_sec += second.tm_sec;
    tmp.tm_min += second.tm_min;
    tmp.tm_hour += second.tm_hour;
    tmp.tm_mday += second.tm_mday;
    tmp.tm_mon += second.tm_mon;
    tmp.tm_year += second.tm_year;
    tmp.tm_isdst = -1;
    //::mktime(&tmp);
    return tmp;
}

tm operator-(const tm& first,const tm& second)
{
    tm tmp;
    ::memcpy(&tmp,&first,sizeof(tm));
    tmp.tm_sec -= second.tm_sec;
    tmp.tm_min -= second.tm_min;
    tmp.tm_hour -= second.tm_hour;
    tmp.tm_mday -= second.tm_mday;
    tmp.tm_mon -= second.tm_mon;
    tmp.tm_year -= second.tm_year;
    tmp.tm_isdst = -1;
    //::mktime(&tmp);
    return tmp;
}

