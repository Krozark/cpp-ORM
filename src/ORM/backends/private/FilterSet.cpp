#include <ORM/backends/private/FilterSet.hpp>

namespace orm
{
    FilterSet::~FilterSet()
    {
        if(type == LEAF)
        {
            delete (VFilter*)right;
        }
        else
        {
            delete right;
            delete left;
        }
    }



    FilterSet::FilterSet(const std::string& op,const FilterSet* f) : left(f), op(op), right(nullptr), type(UNARY)
    {
    }
    
    FilterSet::FilterSet(const FilterSet* left,const std::string& op,const FilterSet* right) : left(left), op(op), right(right), type(BINARY)
    {
    }

    void FilterSet::__print__() const
    {
        switch (type)
        {
            case LEAF :
                ((VFilter*)left)->__print__();
                break;
            case UNARY:
                std::cout<<op<<" ";
                left->__print__();
                break;
            case BINARY:
                std::cout<<"(";
                left->__print__();
                std::cout<<" "<<op<<" ";
                right->__print__(); 
                std::cout<<")";
                break;
            default:
                break;
        }
    }

    bool FilterSet::set(Query* query,unsigned int& column) const
    {
        bool res;
        switch (type)
        {
            case LEAF :
                res = ((VFilter*)left)->set(query,column);
                break;
            case UNARY:
                res = left->set(query,column);
                break;
            case BINARY:
                res = left->set(query,column);
                ++column;
                res= res and right->set(query,column);
                break;
            default:
                break;
        }
        return res;
    }

    void FilterSet::toQuery(std::string& query,Bdd& bdd) const
    {
        switch (type)
        {
            case LEAF :
                ((VFilter*)left)->toQuery(query,bdd);
                break;
            case UNARY:
                query+=op;
                left->toQuery(query,bdd); 
                break;
            case BINARY:
                left->toQuery(query,bdd);
                query+=op;
                right->toQuery(query,bdd); 
                break;
            default:
                break;
        }
    }

    FilterSet operator!(const FilterSet& a)
    {
        return FilterSet("NOT",&a);
    }

    FilterSet operator&&(const FilterSet& a, const FilterSet& b)
    {
        return FilterSet(&a,"AND",&b);
    }

    FilterSet operator||(const FilterSet& a,const FilterSet& b)
    {
        return FilterSet(&a,"OR",&b);
    }

    FilterSet operator&&(FilterSet&& a, FilterSet&& b)
    {
        return FilterSet(new FilterSet(std::move(a)),"AND",new FilterSet(std::move(b)));
    }

    FilterSet operator||(FilterSet&& a, FilterSet&& b)
    {
        return FilterSet(new FilterSet(std::move(a)),"OR",new FilterSet(std::move(b)));
    }

}
