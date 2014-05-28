namespace orm
{
    template<typename RELATED,typename T>
    FilterSet::FilterSet(Filter<RELATED,T>&& f): left(new Filter<RELATED,T>(std::forward<Filter<RELATED,T>>(f))), ope(), right(nullptr), type(LEAF)
    {
    };
}
