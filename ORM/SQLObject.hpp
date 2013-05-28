#ifndef ORM_SQLOBJECT_HPP
#define ORM_SQLOBJECT_HPP

#include "SQLObjectBase.hpp"


#include "VAttr.hpp" 


namespace orm
{
    class Bdd;
    class Query;

    template<typename T>
    class SQLObject : public SQLObjectBase
    {
        public:
            SQLObject();

            SQLObject(const SQLObject&) = delete;
            SQLObject& operator=(const SQLObject&) = delete;
            
            static T* createFromBdd(const Query& query);
            static T* get(unsigned int id);
            static std::list<T*> filter();
            static std::list<T*> all();

            virtual bool save(bool force=false);
            virtual bool del();

            static  Bdd* bdd_used;
        protected:
            const static std::string table;
    };
};

#define REGISTER_TABLE(T,tab) \
    template<>\
    const std::string orm::SQLObject<T>::table = tab;\
    template<>\
    orm::Bdd* orm::SQLObject<T>::bdd_used = &orm::Bdd::Default;

#define REGISTER_BDD(T,bdd) \
    orm::SQLObject<T>::bdd_used = bdd;

#define _MAKE_STRING_0(prefix) {}
#define _MAKE_STRING_2(prefix,name,value) const std::string prefix ## _ ## name = value;
#define _MAKE_STRING_4(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_2(prefix,__VA_ARGS__)
#define _MAKE_STRING_6(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_4(prefix,__VA_ARGS__)
#define _MAKE_STRING_8(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_6(prefix,__VA_ARGS__)
#define _MAKE_STRING_10(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_8(prefix,__VA_ARGS__)
#define _MAKE_STRING_12(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_10(prefix,__VA_ARGS__)
#define _MAKE_STRING_14(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_12(prefix,__VA_ARGS__)
#define _MAKE_STRING_16(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_14(prefix,__VA_ARGS__)
#define _MAKE_STRING_18(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_16(prefix,__VA_ARGS__)
#define _MAKE_STRING_20(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_18(prefix,__VA_ARGS__)
#define _MAKE_STRING_22(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_20(prefix,__VA_ARGS__)
#define _MAKE_STRING_24(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_22(prefix,__VA_ARGS__)
#define _MAKE_STRING_26(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_24(prefix,__VA_ARGS__)
#define _MAKE_STRING_28(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_26(prefix,__VA_ARGS__)
#define _MAKE_STRING_30(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_28(prefix,__VA_ARGS__)
#define _MAKE_STRING_32(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_30(prefix,__VA_ARGS__)
#define _MAKE_STRING_34(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_32(prefix,__VA_ARGS__)
#define _MAKE_STRING_36(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_34(prefix,__VA_ARGS__)
#define _MAKE_STRING_38(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_36(prefix,__VA_ARGS__)
#define _MAKE_STRING_40(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_38(prefix,__VA_ARGS__)
#define _MAKE_STRING_42(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_40(prefix,__VA_ARGS__)
#define _MAKE_STRING_44(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_42(prefix,__VA_ARGS__)
#define _MAKE_STRING_46(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_44(prefix,__VA_ARGS__)
#define _MAKE_STRING_48(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_46(prefix,__VA_ARGS__)
#define _MAKE_STRING_50(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_48(prefix,__VA_ARGS__)
#define _MAKE_STRING_52(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_50(prefix,__VA_ARGS__)
#define _MAKE_STRING_54(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_52(prefix,__VA_ARGS__)
#define _MAKE_STRING_56(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_54(prefix,__VA_ARGS__)
#define _MAKE_STRING_58(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_56(prefix,__VA_ARGS__)
#define _MAKE_STRING_60(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_58(prefix,__VA_ARGS__)
#define _MAKE_STRING_62(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_60(prefix,__VA_ARGS__)
#define _MAKE_STRING_64(prefix,name,value,...) const std::string prefix ## _ ## name = value; _MAKE_STRING_62(prefix,__VA_ARGS__)


#define MAKE_STRINGS(prefix,name,value,...) \
    MAKE_STRING(prefix,name,value) \
    MAKE_STRINGS(prefix,__VA_ARGS__)

// NUM_ARGS(...) evaluates to the literal number of the passed-in arguments.
#define _NUM_ARGS2(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N

#define NUM_ARGS(...) _NUM_ARGS2(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)


#define _MAKE_STRING_N1(klass,N,...) _MAKE_STRING_##N(klass,__VA_ARGS__)
#define _MAKE_STRING_N(klass,N,...) _MAKE_STRING_N1(klass,N,__VA_ARGS__)

#define MAKE_CONSTRUCTOR(klass,...) \
        _MAKE_STRING_N(klass,NUM_ARGS(__VA_ARGS__),__VA_ARGS__)\
        klass::klass(): name(klass##_name), pv(klass##_pv), lvl(klass##_lvl){}


//#define MY_MACRO(...) decltype(FIRST_ARG(__VA_ARGS__))

#include "SQLObject.tpl"
#endif
