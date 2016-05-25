#include <ORM/core/from_string.hpp>
#include <algorithm>

#include <iostream>
#include <sstream>
//#include <locale>

namespace orm
{
    template <>
    bool from_string<int>(const std::string& str, int& value)
    {
        try
        {
            value = std::stoi(str);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }

    template <>
    bool from_string<bool>(const std::string& str, bool& value)
    {
        int i = value;
        if (from_string<int>(str, i))
        {
            value = i;
        }
        else
        {
            std::string data = str;
            std::transform(data.begin(), data.end(), data.begin(), ::tolower);
            if (str == "true")
            {
                value = true;
            }
            else if (str == "false")
            {
                value = false;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    template <>
    bool from_string< unsigned int>(const std::string& str, unsigned int& value)
    {
        try
        {
            value = std::stoul(str);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }

    template <>
    bool from_string< long long int>(const std::string& str, long long int& value)
    {
        try
        {
            value = std::stoll(str);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }

    template <>
    bool from_string< unsigned long long int>(const std::string& str, unsigned long long int& value)
    {
        try
        {
            value = std::stoull(str);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }

    template <>
    bool from_string< float>(const std::string& str, float& value)
    {
        try
        {
            value = std::stof(str);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }

    template <>
    bool from_string< double>(const std::string& str, double& value)
    {
        try
        {
            value = std::stod(str);
        }
        catch(...)
        {
            return false;
        }
        return true;

    }

    template <>
    bool from_string< long double>(const std::string& str, long double& value)
    {
        try
        {
            value = std::stold(str);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }

    template <>
    bool from_string<tm>(const std::string& str, tm& value)
    {
        std::string format("%4d-%2d-%2d %2d:%2d:%2d");

        int day = 0;
        int month = 0;
        int year = 0;
        int hour = 0;
        int min = 0;
        int sec = 0;

        if (sscanf(str.c_str(), format.c_str(), &day, &month, &year, &hour, &min, &sec) != 6)
        {
            return false;
        }

        value.tm_mday = day;
        value.tm_mon = month;
        value.tm_year = year;
        value.tm_hour = hour;
        value.tm_min = min;
        value.tm_sec = sec;

        return true;
    }
}
