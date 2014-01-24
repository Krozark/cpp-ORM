namespace orm
{
    template<typename T>
    Filter<T>::Filter(const std::string& column,const std::string& ope,const T& value) : VFilter(column,ope), value(value)
    {
    };

    template<typename T>
    Filter<T>::Filter(std::string&& column,const std::string& ope,const T& value) : VFilter(column,ope), value(value)
    {
    };

    template<typename T>
    Filter<T>::~Filter()
    {
    };


    template<typename T>
    void Filter<T>::__print__() const
    {
        std::cout<<"column:"<<column<<" operator:"<<ope<<" value:"<<value;
    };

    template<typename T>
    bool Filter<T>::set(Query* query,unsigned int& column) const
    {
        return query->set(value,column);
    }

    template<>
    bool Filter<std::string>::set(Query* query,unsigned int& column) const
    {
        std::string v(query->bdd.formatValue(ope,value));
        return query->set(v,column);
    }
}
