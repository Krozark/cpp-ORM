#include <sstream>

namespace orm
{
    template<typename T>
    template<typename ... Args>
    Filter<T>::Filter(const T& value,const std::string& ope,const std::string& column,Args&& ... args) : column(column), ope(ope), value(value)
    {
    };

    template<typename T>
    Filter<T>::~Filter()
    {
    };


    template<typename T>
    void Filter<T>::__print__(const Bdd& bdd) const
    {
        const std::string& op = bdd.operators.at(ope);

        std::string v;
        {
            std::stringstream ss;
            ss<<value;
            v=ss.str();
        }

        char buffer[ope.size() + v.size()];
        sprintf(buffer,op.c_str(),v.c_str());

        std::cout<<column<<" "<<buffer;
    };

    template<typename T>
    VFilter* Filter<T>::clone() const
    {
        return new Filter<T>(value,ope,column);
    };

    template<typename T>
    bool Filter<T>::set(Query* query,unsigned int& column) const
    {
        return query->set(value,column);
    }
    
    template<typename T>
    void Filter<T>::toQuery(std::string& query,Bdd& bdd) const
    {
        query += column + bdd.formatPreparedValue(ope);
    }

    template <typename T, typename ... Args>
    Filter<T> Q(T&& value,Args&& ... args)
    {
        return Filter<T>(std::forward<T>(value),std::forward<Args>(args)...);
    }
}
