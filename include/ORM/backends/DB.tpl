namespace orm
{
    template<typename T>
    T DB::formatValue(const std::string& ope,T value) const
    {
        return value;
    }
}
