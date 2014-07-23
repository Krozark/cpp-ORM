#ifndef ORM_DATETIMEFIELD_HPP
#define ORM_DATETIMEFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

#include <ctime>

namespace orm
{
    class DateTimeField : public Attr<struct tm>
    {
        public:
            DateTimeField(const struct tm& value,const std::string& column);

            DateTimeField(const std::string& column);


            int& year();
            int& month();
            int& day();
            int& hour();
            int& minute();
            int& second();
            int& yday();

            std::time_t mktime();

            virtual std::ostream& print_value(std::ostream& output)const;

            using Attr<struct tm>::operator tm;
            struct tm& operator=(const struct tm& other);


            static struct tm now();
            static struct tm time(int hour,int min,int sec);
            static struct tm time();
            static struct tm date(int year,int month,int day);
            static struct tm day(int nb);
            static struct tm month(int nb);
            static struct tm year(int nb);
            static struct tm& normalize(struct tm& time);
            static struct tm normalize(struct tm&& time);

        protected:
            //bool auto_now;
            //bool auto_now_add;

            virtual struct tm prepare_to_db(const struct tm& value);

            virtual struct tm prepare_from_db(const struct tm& value);

            virtual std::string create(const DB& db) const;

        private:
    };
}
std::ostream& operator<<(std::ostream& stream,const struct tm& time);

bool operator>(const struct tm& first,const struct tm& second);
bool operator>=(const struct tm& first,const struct tm& second);
bool operator<(const struct tm& first,const struct tm& second);
bool operator<=(const struct tm& first,const struct tm& second);
bool operator==(const struct tm& first,const struct tm& second);

struct tm operator+(const struct tm& first,const struct tm& second);
struct tm operator-(const struct tm& first,const struct tm& second);

#endif
