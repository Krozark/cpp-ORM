namespace orm
{
    template<typename T>
    FilterSet::FilterSet(Filter<T>&& f): left(new Filter<T>(std::forward<Filter<T>>(f))), ope(), right(nullptr), type(LEAF)
    {
    };
}
