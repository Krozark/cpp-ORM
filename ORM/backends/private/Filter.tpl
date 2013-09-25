namespace orm
{
    template<typename T>
    Filter<T>::Filter(const std::string& colum,const std::string& ope,const T& value) : VFilter(colum,ope), value(value)
    {
    };

    template<typename T>
    Filter<T>::Filter(std::string&& colum,const std::string& ope,const T& value) : VFilter(colum,ope), value(value)
    {
    };

    template<typename T>
    void Filter<T>::__print__() const
    {
        std::cout<<"column:"<<colum<<" operator:"<<ope<<" value:"<<value;
    };

    template<typename T>
    bool Filter<T>::set(Query* query,unsigned int& colum) const
    {
        return query->set(value,colum);
    }
}
