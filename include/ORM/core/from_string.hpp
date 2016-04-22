#ifndef ORM_FROM_STRING_HPP
#define ORM_FROM_STRING_HPP

#include <string>
#include <ctime>

namespace orm 
{
	template <typename T>
	bool from_string(const std::string& str,T& value);
	
    template <>
    bool from_string<bool>(const std::string& str, bool& value);

	template <>
	bool from_string<int>(const std::string& str, int& value);

    template <>
    bool from_string< unsigned int>(const std::string& str, unsigned int& value);

    template <>
    bool from_string< long long int>(const std::string& str, long long int& value);

    template <>
    bool from_string< unsigned long long int>(const std::string& str, unsigned long long int& value);

    template <>
    bool from_string< float>(const std::string& str, float& value);

    template <>
    bool from_string< double>(const std::string& str, double& value);

    template <>
    bool from_string< long double>(const std::string& str, long double& value);

    template <>
    bool from_string<tm>(const std::string& str, tm& value);

}

#include <ORM/core/from_string.tpl>

#endif