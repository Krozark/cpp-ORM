#include <ORM/backends/private/FilterSet.hpp>

namespace orm
{

    FilterSet::FilterSet(FilterSet&& a) : left(nullptr), ope(), right(nullptr), type(a.type)
    {
        std::swap(left,a.left);
        std::swap(ope,a.ope);
        std::swap(right,a.right);
    }

    FilterSet::FilterSet(const FilterSet& a) :ope(a.ope), type(a.type)
    {
        switch(type)
        {
            case LEAF:
                left = reinterpret_cast<VFilter*>(a.left)->clone();
                right = nullptr;
                break;
            case UNARY:
                left = new FilterSet(*reinterpret_cast<FilterSet*>(a.left));
                right = nullptr;
                break;
            case BINARY:
                left = new FilterSet(*reinterpret_cast<FilterSet*>(a.left));
                right = new FilterSet(*a.right);
                break;
        }
    }

    FilterSet::FilterSet(FilterSet&& l, const std::string& o) : left(new FilterSet(std::forward<FilterSet>(l))), ope(o), right(nullptr), type(UNARY)
    {
    }

    FilterSet::FilterSet(const FilterSet& l, const std::string& o) : left(new FilterSet(l)), ope(o), right(nullptr), type(UNARY)
    {
    }

    FilterSet::FilterSet(FilterSet&& l, const std::string o,FilterSet&& r) : left(new FilterSet(std::forward<FilterSet>(l))), ope(o), right(new FilterSet(std::forward<FilterSet>(r))), type(BINARY)
    {
    }

    FilterSet::~FilterSet()
    {
        if(type == LEAF)
            delete reinterpret_cast<VFilter*>(left);
        else
        {
            delete reinterpret_cast<FilterSet*>(left);
            delete right;
        }
    }

    void FilterSet::__print__(const DB& db)const
    {
        switch(type)
        {
            case LEAF:
            {
                reinterpret_cast<VFilter*>(left)->__print__(db);
            }break;
            case UNARY:
            {
                std::cout<<"("<<ope<<" ";
                reinterpret_cast<FilterSet*>(left)->__print__(db);
                std::cout<<")";
            }break;
            case BINARY:
            {
                std::cout<<"(";
                reinterpret_cast<const FilterSet*>(left)->__print__(db);
                std::cout<<" "<<ope<<" ";
                right->__print__(db);
                std::cout<<")";
            }break;
        }
    }

    FilterSet operator!(FilterSet&& f){
        return FilterSet(std::forward<FilterSet>(f),"NOT");
    }

    FilterSet operator!(const FilterSet& f){
        return FilterSet(f,"NOT");
    }

    FilterSet operator&&(FilterSet&& a,FilterSet&& b){
        return FilterSet(std::forward<FilterSet>(a),"AND",std::forward<FilterSet>(b));
    }

    FilterSet operator||(FilterSet&& a,FilterSet&& b){
        return FilterSet(std::forward<FilterSet>(a),"OR",std::forward<FilterSet>(b));
    }

    bool FilterSet::set(Query* query,unsigned int& column) const
    {
        bool res;
        switch (type)
        {
            case LEAF :
                res = reinterpret_cast<VFilter*>(left)->set(query,column);
                break;
            case UNARY:
                res = reinterpret_cast<FilterSet*>(left)->set(query,column);
                break;
            case BINARY:
                res = reinterpret_cast<FilterSet*>(left)->set(query,column);
                ++column;
                res= res and right->set(query,column);
                break;
            default:
                break;
        }
        return res;
    }

    void FilterSet::toQuery(std::string& query,DB& db) const
    {
        switch (type)
        {
            case LEAF :
                reinterpret_cast<VFilter*>(left)->toQuery(query,db);
                break;
            case UNARY:
                query+="("+ope+" ";
                reinterpret_cast<FilterSet*>(left)->toQuery(query,db); 
                query+=")";
                break;
            case BINARY:
                query+="(";
                reinterpret_cast<FilterSet*>(left)->toQuery(query,db);
                query+=" "+ope+" ";
                right->toQuery(query,db); 
                query+=")";
                break;
            default:
                break;
        }
    }
}
