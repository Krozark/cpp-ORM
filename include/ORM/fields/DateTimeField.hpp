#ifndef ORM_DATETIMEFIELD_HPP
#define ORM_DATETIMEFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

#include <ctime>

namespace orm
{
    /**
     * \brief a field classe to store datetime types.
     * Internaly use struct tm as localtime (from time.h)
     */
    class DateTimeField : public Attr<tm>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/            
            DateTimeField(const tm& value,const std::string& column);

            /**
             * \brief Make a Attr
             *  default value is false.
             * \param column Column in db
             * 
             **/
            DateTimeField(const std::string& column);


            int& year();///\return the year (format = xxxx)
            int& month(); ///\return the month (format = 1~12)
            int& day(); ///\return the day (format = 0~31)
            int& hour(); ///\return the hours
            int& minute(); ///\return the minutes
            int& second();///\return the second
            int& yday();///\return the number of days sinc 1st january

            /**
             * \brief normalize the internal struct
             * \return the timestamp
             */
            std::time_t mktime();

            /**
             * \brief print the value
             */
            virtual std::ostream& print_value(std::ostream& output)const;

            using Attr<tm>::operator tm;///\brief cast operator

            tm& operator=(const tm& other);


            static tm now();///\return the localtime now

            /**
             * \brief construct a tm struct with spécified value
             * \param hour the hour (can be greater than 24)
             * \param min the minutes (can be greater than 59)
             * \param sec the second (can be greater than 59)
             */
            static tm time(int hour,int min,int sec);

            /**
             * \brief construct a tm struct with spécified value
             */
            static tm date(int year,int month,int day);

            static tm day(int nb);///\retrun a tm struc of values of nb days
            static tm month(int nb); ///\return a tm struct of nb months
            static tm year(int nb);///\return a tm struct of nb days

            /**
             * \brief normalize the param
             * \param time tm to normalize
             * \return the param
             */
            static tm& normalize(tm& time);

            /**
             * \brief normalize the param
             * \param time tm to normalize
             * \return the param
             */
            static tm normalize(tm&& time);

        private:
            
            virtual tm prepare_to_db(const tm& value) override;///< convert t to real time (add +1900 y and +1 month)

            virtual tm prepare_from_db(const tm& value) override; ///< convert DB to tm

            virtual std::string create(const DB& db) const override; ///< get creator

    };

    /**
     * \brief Same as DateTimeField, but the value is now on first save
     */
    class AutoDateTimeField : public DateTimeField
    {
        public:
            /**
            * \brief Make a Attr
            *
            * \param value value to store
            * \param column Column in db
            **/
            AutoDateTimeField(const tm& value, const std::string& column);

            /**
            * \brief Make a Attr
            *  default value is false.
            * \param column Column in db
            *
            **/
            AutoDateTimeField(const std::string& column);

            using DateTimeField::operator tm;
            using DateTimeField::operator=;

        protected:
            virtual void before_save();
    };

    /**
     * \brief Same as DateTimeField, but the value is now on each save or update on the
     * Object owner
     */
    class AutoNowDateTimeField : public DateTimeField
    {
        public:
            /**
            * \brief Make a Attr
            *
            * \param value value to store
            * \param column Column in db
            **/
            AutoNowDateTimeField(const tm& value, const std::string& column);

            /**
            * \brief Make a Attr
            *  default value is false.
            * \param column Column in db
            *
            **/
            AutoNowDateTimeField(const std::string& column);

            using DateTimeField::operator tm;
            using DateTimeField::operator=;

        protected:
            virtual void before_save();
            virtual void before_update();
    };
}

std::ostream& operator<<(std::ostream& stream,const tm& time);///\print a tm as "YYYY-MM-DD HH:MM:SS"

bool operator>(const tm& first,const tm& second);
bool operator>=(const tm& first,const tm& second);
bool operator<(const tm& first,const tm& second);
bool operator<=(const tm& first,const tm& second);
bool operator==(const tm& first,const tm& second);

tm operator+(const tm& first,const tm& second);
tm operator-(const tm& first,const tm& second);

#endif
