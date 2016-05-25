#include <type_traits>

namespace orm
{
	template <typename T>
    bool from_string(const std::string& str, T& value)
    {
        static_assert(std::is_convertible<std::string, T>::value,
            "Impossible to convert T from std::string. Please make your own from_string() function");
        value = str;
        return true;
    }
}
