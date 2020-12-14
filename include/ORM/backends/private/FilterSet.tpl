namespace orm
{
    template<typename RELATED>
    template<typename T>
    FilterSet<RELATED>::FilterSet(Filter<RELATED,T>&& f):
        _left(new Filter<RELATED,T>(std::forward<Filter<RELATED,T>>(f))),
        _ope(),
        _right(nullptr),
        _type(LEAF)
    {
    };

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(FilterSet<RELATED>&& a) :
        _left(nullptr),
        _ope(),
        _right(nullptr),
        _type(a._type)
    {
        std::swap(_left,a._left);
        std::swap(_ope,a._ope);
        std::swap(_right,a._right);
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(const FilterSet<RELATED>& a) :
        _ope(a._ope),
        _type(a._type)
    {
        switch(_type)
        {
            case LEAF:
            {
                _left = reinterpret_cast<VFilter*>(a.left)->_clone();
                _right = nullptr;
            }break;
            case UNARY:
            {
                _left = new FilterSet<RELATED>(*reinterpret_cast<FilterSet<RELATED>*>(a._left));
                _right = nullptr;
            }break;
            case BINARY:
            {
                _left = new FilterSet<RELATED>(*reinterpret_cast<FilterSet<RELATED>*>(a._left));
                _right = new FilterSet<RELATED>(*a._right);
            }break;
        }
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(FilterSet<RELATED>&& l, const std::string& o) :
        _left(new FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(l))),
        _ope(o),
        _right(nullptr),
        _type(UNARY)
    {
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(const FilterSet<RELATED>& l, const std::string& o) :
        _left(new FilterSet<RELATED>(l)),
        _ope(o),
        _right(nullptr),
        _type(UNARY)
    {
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(FilterSet<RELATED>&& l, const std::string o,FilterSet<RELATED>&& r) :
        _left(new FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(l))),
        _ope(o),
        _right(new FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(r))),
        _type(BINARY)
    {
    }

    template<typename RELATED>
    FilterSet<RELATED>::~FilterSet()
    {
        if(_type == LEAF)
        {
            delete reinterpret_cast<VFilter*>(_left);
        }
        else
        {
            delete reinterpret_cast<FilterSet<RELATED>*>(_left);
            delete _right;
        }
    }

    template<typename RELATED>
    void FilterSet<RELATED>::debugPrint(const DB& db)const
    {
        switch(_type)
        {
            case LEAF:
            {
                reinterpret_cast<VFilter*>(_left)->debugPrint(db);
            }break;
            case UNARY:
            {
                std::cout<<"("<<_ope<<" ";
                reinterpret_cast<FilterSet<RELATED>*>(_left)->debugPrint(db);
                std::cout<<")";
            }break;
            case BINARY:
            {
                std::cout<<"(";
                reinterpret_cast<const FilterSet<RELATED>*>(_left)->debugPrint(db);
                std::cout<<" "<<_ope<<" ";
                _right->debugPrint(db);
                std::cout<<")";
            }break;
        }
    }


    template<typename RELATED>
    bool FilterSet<RELATED>::_set(Query& query,unsigned int& column) const
    {
        bool res = false;
        switch (_type)
        {
            case LEAF :
            {
                res = reinterpret_cast<VFilter*>(_left)->_set(query,column);
            }break;
            case UNARY:
            {
                res = reinterpret_cast<FilterSet*>(_left)->_set(query,column);
            }break;
            case BINARY:
            {
                res = reinterpret_cast<FilterSet<RELATED>*>(_left)->_set(query,column);
                ++column;
                res= (res and _right->_set(query,column));
            }break;
            default:
            {
            }break;
        }
        return res;
    }

    template<typename RELATED>
    void FilterSet<RELATED>::_toQuery(std::string& query,DB& db) const
    {
        switch (_type)
        {
            case LEAF :
            {
                reinterpret_cast<VFilter*>(_left)->_toQuery(query,db);
            }break;
            case UNARY:
            {
                query+="("+_ope+" ";
                reinterpret_cast<FilterSet<RELATED>*>(_left)->_toQuery(query,db);
                query+=")";
            }break;
            case BINARY:
            {
                query+="(";
                reinterpret_cast<FilterSet<RELATED>*>(_left)->_toQuery(query,db);
                query+=" "+_ope+" ";
                _right->_toQuery(query,db);
                query+=")";
            }break;
            default:
            {
            }break;
        }
    }


    template<typename RELATED>
    FilterSet<RELATED> operator!(FilterSet<RELATED>&& f)
    {
        return FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(f),"NOT");
    }

    template<typename RELATED>
    FilterSet<RELATED> operator!(const FilterSet<RELATED>& f)
    {
        return FilterSet<RELATED>(f,"NOT");
    }

    template<typename RELATED>
    FilterSet<RELATED> operator&&(FilterSet<RELATED>&& a,FilterSet<RELATED>&& b)
    {
        return FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(a),"AND",std::forward<FilterSet<RELATED>>(b));
    }

    template<typename RELATED>
    FilterSet<RELATED> operator||(FilterSet<RELATED>&& a,FilterSet<RELATED>&& b)
    {
        return FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(a),"OR",std::forward<FilterSet<RELATED>>(b));
    }

    template <typename RELATED,typename T, typename ... Args>
    FilterSet<RELATED> Q(const T& value,Args&& ... args)
    {
        Filter<RELATED,T> tmp(value,std::forward<Args>(args)...);
        return FilterSet<RELATED>(std::move(tmp));
    }
}
