#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

#include "SQLObjectBase.hpp"


#include "VAttr.hpp" 


namespace orm
{
    class Bdd;
    class Query;
    class Filter;

    template<typename T>
    class SQLObject : public SQLObjectBase
    {
        public:
            SQLObject();

            SQLObject(const SQLObject&) = delete;
            SQLObject& operator=(const SQLObject&) = delete;
            
            static T* createFromBdd(const Query& query);
            static T* get(unsigned int id);
            static std::list<T*> all();
            
            template<typename U>
            static std::list<T*> filter(const std::string& colum,const std::string& ope,const U& value);
            static std::list<T*> filter(const Filter& filter);
            static std::list<T*> filter(const std::list<Filter>& filters);


            virtual bool save(bool force=false);
            virtual bool del();

            static  Bdd* bdd_used;
        protected:
            const static std::string table;
    };
};

//make string name for attrs
#define _MAKE_NAME(prefix,name) prefix ## _ ## name

//make string initialisation for attrs
#define _MAKE_STRING_0(klass) {}
#define _MAKE_STRING_2(klass,name,value) const std::string _MAKE_NAME(klass,name) = value;
#define _MAKE_STRING_4(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_2(klass,__VA_ARGS__)
#define _MAKE_STRING_6(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_4(klass,__VA_ARGS__)
#define _MAKE_STRING_8(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_6(klass,__VA_ARGS__)
#define _MAKE_STRING_10(klass,name,value,...) const std::string _MAKE_NAME(klass,name)  = value; _MAKE_STRING_8(klass,__VA_ARGS__)
#define _MAKE_STRING_12(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_10(klass,__VA_ARGS__)
#define _MAKE_STRING_14(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_12(klass,__VA_ARGS__)
#define _MAKE_STRING_16(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_14(klass,__VA_ARGS__)
#define _MAKE_STRING_18(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_16(klass,__VA_ARGS__)
#define _MAKE_STRING_20(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_18(klass,__VA_ARGS__)
#define _MAKE_STRING_22(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_20(klass,__VA_ARGS__)
#define _MAKE_STRING_24(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_22(klass,__VA_ARGS__)
#define _MAKE_STRING_26(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_24(klass,__VA_ARGS__)
#define _MAKE_STRING_28(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_26(klass,__VA_ARGS__)
#define _MAKE_STRING_30(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_28(klass,__VA_ARGS__)
#define _MAKE_STRING_32(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_30(klass,__VA_ARGS__)
#define _MAKE_STRING_34(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_32(klass,__VA_ARGS__)
#define _MAKE_STRING_36(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_34(klass,__VA_ARGS__)
#define _MAKE_STRING_38(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_36(klass,__VA_ARGS__)
#define _MAKE_STRING_40(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_38(klass,__VA_ARGS__)
#define _MAKE_STRING_42(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_40(klass,__VA_ARGS__)
#define _MAKE_STRING_44(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_42(klass,__VA_ARGS__)
#define _MAKE_STRING_46(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_44(klass,__VA_ARGS__)
#define _MAKE_STRING_48(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_46(klass,__VA_ARGS__)
#define _MAKE_STRING_50(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_48(klass,__VA_ARGS__)
#define _MAKE_STRING_52(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_50(klass,__VA_ARGS__)
#define _MAKE_STRING_54(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_52(klass,__VA_ARGS__)
#define _MAKE_STRING_56(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_54(klass,__VA_ARGS__)
#define _MAKE_STRING_58(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_56(klass,__VA_ARGS__)
#define _MAKE_STRING_60(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_58(klass,__VA_ARGS__)
#define _MAKE_STRING_62(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_60(klass,__VA_ARGS__)
#define _MAKE_STRING_64(klass,name,value,...) const std::string _MAKE_NAME(klass,name) = value; _MAKE_STRING_62(klass,__VA_ARGS__)
//init call
#define _MAKE_STRING_N1(klass,N,...) _MAKE_STRING_##N(klass,__VA_ARGS__)
#define _MAKE_STRING_N(klass,N,...) _MAKE_STRING_N1(klass,N,__VA_ARGS__)

//call Attr constructor
#define _MAKE_ATTR_0() 
#define _MAKE_ATTR_2(klass,name,value) name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_4(klass,name,value,...) _MAKE_ATTR_2(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_6(klass,name,value,...) _MAKE_ATTR_4(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_8(klass,name,value,...) _MAKE_ATTR_6(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_10(klass,name,value,...) _MAKE_ATTR_8(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_12(klass,name,value,...) _MAKE_ATTR_10(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_14(klass,name,value,...) _MAKE_ATTR_12(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_16(klass,name,value,...) _MAKE_ATTR_14(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_18(klass,name,value,...) _MAKE_ATTR_16(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_20(klass,name,value,...) _MAKE_ATTR_18(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_22(klass,name,value,...) _MAKE_ATTR_20(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_24(klass,name,value,...) _MAKE_ATTR_22(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_26(klass,name,value,...) _MAKE_ATTR_24(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_28(klass,name,value,...) _MAKE_ATTR_26(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_30(klass,name,value,...) _MAKE_ATTR_28(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_32(klass,name,value,...) _MAKE_ATTR_30(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_34(klass,name,value,...) _MAKE_ATTR_32(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_36(klass,name,value,...) _MAKE_ATTR_34(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_38(klass,name,value,...) _MAKE_ATTR_36(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_40(klass,name,value,...) _MAKE_ATTR_38(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_42(klass,name,value,...) _MAKE_ATTR_40(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_44(klass,name,value,...) _MAKE_ATTR_42(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_46(klass,name,value,...) _MAKE_ATTR_44(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_48(klass,name,value,...) _MAKE_ATTR_46(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_50(klass,name,value,...) _MAKE_ATTR_48(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_52(klass,name,value,...) _MAKE_ATTR_50(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_54(klass,name,value,...) _MAKE_ATTR_52(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_56(klass,name,value,...) _MAKE_ATTR_54(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_58(klass,name,value,...) _MAKE_ATTR_56(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_60(klass,name,value,...) _MAKE_ATTR_58(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_62(klass,name,value,...) _MAKE_ATTR_60(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
#define _MAKE_ATTR_64(klass,name,value,...) _MAKE_ATTR_62(klass,__VA_ARGS__),name(_MAKE_NAME(klass,name))
//init call
#define _MAKE_ATTRS_N1(klass,N,...) _MAKE_ATTR_##N(klass,__VA_ARGS__)
#define _MAKE_ATTRS_N(klass,N,...) _MAKE_ATTRS_N1(klass,N,__VA_ARGS__)

//regsiter ATTR
#define _MAKE_REGISTER_ATTR_0() 
#define _MAKE_REGISTER_ATTR_2(name,value) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_4(name,value,...) _MAKE_REGISTER_ATTR_2(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_6(name,value,...) _MAKE_REGISTER_ATTR_4(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_8(name,value,...) _MAKE_REGISTER_ATTR_6(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_10(name,value,...) _MAKE_REGISTER_ATTR_8(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_12(name,value,...) _MAKE_REGISTER_ATTR_10(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_14(name,value,...) _MAKE_REGISTER_ATTR_12(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_16(name,value,...) _MAKE_REGISTER_ATTR_14(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_18(name,value,...) _MAKE_REGISTER_ATTR_16(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_20(name,value,...) _MAKE_REGISTER_ATTR_18(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_22(name,value,...) _MAKE_REGISTER_ATTR_20(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_24(name,value,...) _MAKE_REGISTER_ATTR_22(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_26(name,value,...) _MAKE_REGISTER_ATTR_24(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_28(name,value,...) _MAKE_REGISTER_ATTR_26(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_30(name,value,...) _MAKE_REGISTER_ATTR_28(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_32(name,value,...) _MAKE_REGISTER_ATTR_30(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_34(name,value,...) _MAKE_REGISTER_ATTR_32(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_36(name,value,...) _MAKE_REGISTER_ATTR_34(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_38(name,value,...) _MAKE_REGISTER_ATTR_36(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_40(name,value,...) _MAKE_REGISTER_ATTR_38(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_42(name,value,...) _MAKE_REGISTER_ATTR_40(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_44(name,value,...) _MAKE_REGISTER_ATTR_42(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_46(name,value,...) _MAKE_REGISTER_ATTR_44(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_48(name,value,...) _MAKE_REGISTER_ATTR_46(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_50(name,value,...) _MAKE_REGISTER_ATTR_48(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_52(name,value,...) _MAKE_REGISTER_ATTR_50(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_54(name,value,...) _MAKE_REGISTER_ATTR_52(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_56(name,value,...) _MAKE_REGISTER_ATTR_54(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_58(name,value,...) _MAKE_REGISTER_ATTR_56(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_60(name,value,...) _MAKE_REGISTER_ATTR_58(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_62(name,value,...) _MAKE_REGISTER_ATTR_60(__VA_ARGS__) this->registerAttr(this->name);
#define _MAKE_REGISTER_ATTR_64(name,value,...) _MAKE_REGISTER_ATTR_62(__VA_ARGS__) this->registerAttr(this->name);
//init call for register attr in constructors
#define _MAKE_REGISTER_ATTRS_N1(N,...) _MAKE_REGISTER_ATTR_##N(__VA_ARGS__)
#define _MAKE_REGISTER_ATTRS(N,...) _MAKE_REGISTER_ATTRS_N1(N,__VA_ARGS__)

// NUM_ARGS(...) evaluates to the literal number of the passed-in arguments.
#define _NUM_ARGS2(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N

#define NUM_ARGS(...) _NUM_ARGS2(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define REGISTER_TABLE(klass,colum) \
    template<>\
    const std::string orm::SQLObject<klass>::table =colum;\
    template<>\
    orm::Bdd* orm::SQLObject<klass>::bdd_used = &orm::Bdd::Default;

#define REGISTER_BDD(klass,bdd) \
    orm::SQLObject<klass>::bdd_used = bdd;


#define MAKE_CONSTRUCTOR(klass,...) \
        _MAKE_STRING_N(klass,NUM_ARGS(__VA_ARGS__),__VA_ARGS__)\
        klass::klass(): _MAKE_ATTRS_N(klass,NUM_ARGS(__VA_ARGS__),__VA_ARGS__)\
        {\
         _MAKE_REGISTER_ATTRS(NUM_ARGS(__VA_ARGS__),__VA_ARGS__)\
        }

#define REGISTER_AND_CONSTRUCT(klass,colum,...) \
        REGISTER_TABLE(klass,colum)\
        MAKE_CONSTRUCTOR(klass,__VA_ARGS__)

#include "SQLObject.tpl"
#endif
