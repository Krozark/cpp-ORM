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
            int year()const;

            int& month();
            int month()const;

            int& day();
            int day()const;

            int& hour();
            int hour()const;

            int& minute();
            int minute()const;

            int& second();
            int second()const;
            
            int& yday();
            int yday()const;


            std::time_t as_timestamp();

            using Attr<struct tm>::operator tm;

            /*DateTimeField& operator>(const DateTimeField& other);
            DateTimeField& operator>=(const DateTimeField& other);
            DateTimeField& operator<(const DateTimeField& other);
            DateTimeField& operator<=(const DateTimeField& other);
            DateTimeField& operator==(const DateTimeField& other);

            DateTimeField& operator+(const DateTimeField& other);
            DateTimeField& operator-(const DateTimeField& other);*/


            bool operator>(const struct tm& other);
            bool operator>=(const struct tm& other);
            bool operator<(const struct tm& other);
            bool operator<=(const struct tm& other);
            bool operator==(const struct tm& other);

            struct tm operator+(const struct tm& other);
            struct tm operator-(const struct tm& other);

            static struct tm now();

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

#endif
