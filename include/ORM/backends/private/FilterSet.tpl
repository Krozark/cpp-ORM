namespace orm
{
    template<typename T>
    FilterSet::FilterSet(const Filter<T>& f) : left((FilterSet*)(new Filter<T>(f))), op(), right(nullptr), type(LEAF)
    {
    }
}
