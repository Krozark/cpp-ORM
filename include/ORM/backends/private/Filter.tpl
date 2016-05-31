#include <sstream>
#include <ctime>
#include <cstring>

namespace orm
{
    //default do nothing
    template<typename T>
    T filter_value_helper_2(const T& value)
    {
        return value;
    };

    //special date type
    template<>
    tm filter_value_helper_2<tm>(const tm& value);

    template<typename RELATED,typename T>
    template<typename ... Args>
    Filter<RELATED,T>::Filter(const T& val,const std::string& ope,const std::string& column,Args&& ... args) :
        _column(DB::_makecolumname(*RELATED::default_connection,RELATED::table,column,std::forward<Args>(args)...)),
        _ope(ope),
        _value(filter_value_helper_2(val))
    {
    };

    template<typename RELATED,typename T>
    Filter<RELATED,T>::Filter(Filter<RELATED,T>&& other) :
        _column(std::move(other._column)),
        _ope(std::move(other._ope)),
        _value(other._value)
    {
    }

    template<typename RELATED,typename T>
    Filter<RELATED,T>::~Filter()
    {
    };


    template<typename RELATED,typename T>
    void Filter<RELATED,T>::debugPrint(const DB& db) const
    {
        const std::string& op = db._operators.at(_ope);

        std::string v;
        {
            std::stringstream ss;
            ss<<_value;
            v=ss.str();
        }

        std::unique_ptr<char> buffer(new char[_ope.size() + v.size()]);
        sprintf(buffer.get(),op.c_str(),v.c_str());

        std::cout<<_column<<" "<< buffer.get();
        //DB::makecolumname(db,OBJ::table,_column,args...)
    };

    //default do nothing
    template<typename T>
    T filter_clone_helper_2(const T& value)
    {
        return value;
    }

    //special date type
    template<>
    tm filter_clone_helper_2<tm>(const tm& value);

    template<typename RELATED,typename T>
    VFilter* Filter<RELATED,T>::_clone() const
    {
        return new Filter<RELATED,T>(filter_clone_helper_2(_value),_ope,_column);
    };

    template<typename RELATED,typename T>
    bool Filter<RELATED,T>::_set(Query* query,unsigned int& column) const
    {
        auto v = query->_db._formatValue(_ope,_value);

        bool res = query->_set(v,column);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        if (not res)
        {
            std::cerr<<ORM_COLOUR_RED<<"[ERROR][Sql:makeQuery] Impossible to bind values <"<<v<<"> on colum "<<column<<ORM_COLOUR_NONE;
        }
        #endif
        return res;

    }

    template<typename RELATED,typename T>
    void Filter<RELATED,T>::_toQuery(std::string& query,DB& db) const
    {
        query += _column + db._formatPreparedValue(_ope);
    }
}
