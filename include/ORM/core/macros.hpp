#ifndef ORM_MACROS_HPP
#define ORM_MACROS_HPP

#include <ORM/externals.hpp>
#include <string>


/** \file */

/**********************************
 ******* for General objects ******
 *********************************/

/**
 * \brief NUM_ARGS(...) evaluates to the literal number of the passed-in arguments.
 **/

//#ifdef ORM_USE_MSVC //visual

#define ORM_EXPAND(x) x
#define ORM_NUM_ARGS_HELPER(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N
#define ORM_NUM_ARGS(...) ORM_EXPAND(ORM_NUM_ARGS_HELPER(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
/*
#else

#define ORM_NUM_ARGS_HELPER(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N
#define ORM_NUM_ARGS(...) ORM_NUM_ARGS_HELPER(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#endif
*/

/**
 * \brief make string name for attrs
 **/
//#ifndef ORM_COLUMN_CHAR
//#define ORM_COLUMN_CHAR $
//#endif

//no space for visual support
#define ORM_MAKE_NAME_HELPER(name)  $##name
#define ORM_MAKE_NAME(name)  ORM_MAKE_NAME_HELPER(name)

#define ORM_MAKE_NAME_VALUE(klass,value)  value

/**
 * \brief make string initialisation for attrs
 **/
#define ORM_MAKE_STRING_0(klass)                 ;
#define ORM_MAKE_STRING_2(klass,name,value)      const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value);
#define ORM_MAKE_STRING_4(klass,name,value,...)  const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_2(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_6(klass,name,value,...)  const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_4(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_8(klass,name,value,...)  const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_6(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_10(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_8(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_12(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_10(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_14(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_12(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_16(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_14(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_18(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_16(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_20(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_18(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_22(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_20(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_24(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_22(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_26(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_24(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_28(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_26(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_30(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_28(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_32(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_30(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_34(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_32(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_36(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_34(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_38(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_36(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_40(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_38(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_42(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_40(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_44(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_42(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_46(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_44(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_48(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_46(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_50(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_48(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_52(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_50(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_54(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_52(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_56(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_54(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_58(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_56(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_60(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_58(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_62(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_60(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_64(klass,name,value,...) const std::string klass::ORM_MAKE_NAME(name) = ORM_MAKE_NAME_VALUE(klass,value); ORM_EXPAND(ORM_MAKE_STRING_62(klass,__VA_ARGS__))
/**
 * \brief init call
 **/
#define ORM_MAKE_STRING_N1(klass,N,...) ORM_EXPAND(ORM_MAKE_STRING_##N(klass,__VA_ARGS__))
#define ORM_MAKE_STRING_N(klass,N,...) ORM_MAKE_STRING_N1(klass,N,__VA_ARGS__)

/**
 * \brief make static const std::string param_name
 **/


#define ORM_ORM_MAKE_STATIC_COLUMN_0            ;
#define ORM_ORM_MAKE_STATIC_COLUMN_1(name)      static const std::string ORM_MAKE_NAME(name);
#define ORM_ORM_MAKE_STATIC_COLUMN_2(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_1(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_3(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_2(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_4(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_3(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_5(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_4(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_6(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_5(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_7(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_6(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_8(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_7(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_9(name,...)  static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_8(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_10(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_9(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_11(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_10(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_12(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_11(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_13(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_12(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_14(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_13(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_15(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_14(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_16(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_15(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_17(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_16(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_18(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_17(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_19(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_18(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_20(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_19(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_21(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_20(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_22(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_21(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_23(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_22(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_24(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_23(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_25(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_24(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_26(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_25(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_27(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_26(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_28(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_27(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_29(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_28(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_30(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_30(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_31(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_31(__VA_ARGS__))
#define ORM_ORM_MAKE_STATIC_COLUMN_32(name,...) static const std::string ORM_MAKE_NAME(name); ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_32(__VA_ARGS__))
/**
 * \brief init call
 **/
#define ORM_ORM_MAKE_STATIC_COLUMN_N1(N,...) ORM_EXPAND(ORM_ORM_MAKE_STATIC_COLUMN_##N(__VA_ARGS__))
#define _ORM_MAKE_STATIC_COLUMN(N,...) ORM_ORM_MAKE_STATIC_COLUMN_N1(N,__VA_ARGS__)

#define ORM_MAKE_STATIC_COLUMN(...) _ORM_MAKE_STATIC_COLUMN(ORM_NUM_ARGS(__VA_ARGS__),__VA_ARGS__)


/********************************
 ******* FOR SqlObject **********
 *******************************/

/**
 * \brief call Attr constructor
 **/
#define ORM_MAKE_ATTR_0()
#define ORM_MAKE_ATTR_2(name,value)      name(ORM_MAKE_NAME(name))
#define ORM_MAKE_ATTR_4(name,value,...)  name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_2(__VA_ARGS__))
#define ORM_MAKE_ATTR_6(name,value,...)  name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_4(__VA_ARGS__))
#define ORM_MAKE_ATTR_8(name,value,...)  name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_6(__VA_ARGS__))
#define ORM_MAKE_ATTR_10(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_8(__VA_ARGS__))
#define ORM_MAKE_ATTR_12(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_10(__VA_ARGS__))
#define ORM_MAKE_ATTR_14(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_12(__VA_ARGS__))
#define ORM_MAKE_ATTR_16(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_14(__VA_ARGS__))
#define ORM_MAKE_ATTR_18(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_16(__VA_ARGS__))
#define ORM_MAKE_ATTR_20(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_18(__VA_ARGS__))
#define ORM_MAKE_ATTR_22(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_20(__VA_ARGS__))
#define ORM_MAKE_ATTR_24(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_22(__VA_ARGS__))
#define ORM_MAKE_ATTR_26(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_24(__VA_ARGS__))
#define ORM_MAKE_ATTR_28(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_26(__VA_ARGS__))
#define ORM_MAKE_ATTR_30(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_28(__VA_ARGS__))
#define ORM_MAKE_ATTR_32(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_30(__VA_ARGS__))
#define ORM_MAKE_ATTR_34(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_32(__VA_ARGS__))
#define ORM_MAKE_ATTR_36(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_34(__VA_ARGS__))
#define ORM_MAKE_ATTR_38(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_36(__VA_ARGS__))
#define ORM_MAKE_ATTR_40(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_38(__VA_ARGS__))
#define ORM_MAKE_ATTR_42(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_40(__VA_ARGS__))
#define ORM_MAKE_ATTR_44(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_42(__VA_ARGS__))
#define ORM_MAKE_ATTR_46(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_44(__VA_ARGS__))
#define ORM_MAKE_ATTR_48(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_46(__VA_ARGS__))
#define ORM_MAKE_ATTR_50(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_48(__VA_ARGS__))
#define ORM_MAKE_ATTR_52(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_50(__VA_ARGS__))
#define ORM_MAKE_ATTR_54(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_52(__VA_ARGS__))
#define ORM_MAKE_ATTR_56(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_54(__VA_ARGS__))
#define ORM_MAKE_ATTR_58(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_56(__VA_ARGS__))
#define ORM_MAKE_ATTR_60(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_58(__VA_ARGS__))
#define ORM_MAKE_ATTR_62(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_60(__VA_ARGS__))
#define ORM_MAKE_ATTR_64(name,value,...) name(ORM_MAKE_NAME(name)), ORM_EXPAND(ORM_MAKE_ATTR_62(__VA_ARGS__))
/**
 * \brief init call
 **/
#define ORMORM_MAKE_ATTRS_N1(N,...) ORM_EXPAND(ORM_MAKE_ATTR_##N(__VA_ARGS__))
#define ORM_MAKE_ATTRS_N(N,...) ORMORM_MAKE_ATTRS_N1(N,__VA_ARGS__)

/**
 * \brief regsiter ATTR
 **/
#define ORM_MAKE_REGISTER_ATTR_0(klass)                 ;
#define ORM_MAKE_REGISTER_ATTR_2(klass,name,value)      this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this));
#define ORM_MAKE_REGISTER_ATTR_4(klass,name,value,...)  this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_2(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_6(klass,name,value,...)  this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_4(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_8(klass,name,value,...)  this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_6(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_10(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_8(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_12(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_10(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_14(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_12(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_16(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_14(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_18(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_16(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_20(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_18(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_22(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_20(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_24(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_22(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_26(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_24(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_28(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_26(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_30(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_28(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_32(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_30(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_34(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_32(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_36(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_34(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_38(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_36(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_40(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_38(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_42(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_40(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_44(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_42(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_46(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_44(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_48(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_46(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_50(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_48(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_52(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_50(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_54(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_52(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_56(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_54(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_58(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_56(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_60(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_58(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_62(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_60(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTR_64(klass,name,value,...) this->name.registerAttr(*static_cast<orm::SqlObject<klass>*>(this)); ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_62(klass,__VA_ARGS__))
/**
 * \brief init call for register attr in constructors
 **/
#define ORM_MAKE_REGISTER_ATTRS_N1(klass,N,...) ORM_EXPAND(ORM_MAKE_REGISTER_ATTR_##N(klass,__VA_ARGS__))
#define ORM_MAKE_REGISTER_ATTRS(klass,N,...) ORM_MAKE_REGISTER_ATTRS_N1(klass,N,__VA_ARGS__)


/**
 * \def ORM_REGISTER_TABLE(klass,column)
 * Register a table in the orm
 */

/**
 * \brief Register a table in the orm
 * \param klass the class name
 * \param column the column name in the db
 */
#define ORM_REGISTER_TABLE(klass,column) \
    template<> const std::string orm::SqlObject<klass>::_table = column;\
    template<> orm::DB* orm::SqlObject<klass>::defaultDBConnection = &orm::DB::Default;\
    template<> std::vector<const orm::VAttr*> orm::SqlObject<klass>::_staticAttributsVector = std::vector<const orm::VAttr*>();\
    template<> std::vector<orm::VFK*> orm::SqlObject<klass>::_staticFksAttributsVector = std::vector<orm::VFK*>();\
    template<> orm::Register<klass> orm::SqlObject<klass>::_register = orm::Register<klass>();\
    template<> orm::Cache<klass> orm::SqlObject<klass>::_cache = orm::Cache<klass>();

/**
 * \brief set the default db to use for this class
 * \param klass the class name
 * \param db the db to use by default
 */
#define ORM_REGISTER_DB(klass,db) \
    orm::SqlObject<klass>::defaultDBConnection = db;

/**
 * \def ORM_REGISTER(klass,column,...)
 * register all the attrs of the tables
 */

/**
 * \brief register all the attrs of the tables
 * \param klass the class name
 * \param colum the table name in the db
 * \param ... is like this (attr name,attr column name)
 */
#define ORM_REGISTER(klass,column,...)\
    ORM_REGISTER_TABLE(klass,column)\
    ORM_MAKE_STRING_N(klass,ORM_NUM_ARGS(__VA_ARGS__),__VA_ARGS__)

/**
 * \def ORM_MAKE_CONSTRUCTOR(klass,...)
 * make the default constructor
 */

/**
 * \brief make the default constructor
 * \param klass the class name
 * \param ... is like this (attr name,attr colum name)
 */
#define ORM_MAKE_CONSTRUCTOR(NAMESPACE,klass,...) \
        NAMESPACE klass::klass(): ORM_MAKE_ATTRS_N(ORM_NUM_ARGS(__VA_ARGS__),__VA_ARGS__)\
        {\
         ORM_MAKE_REGISTER_ATTRS(klass,ORM_NUM_ARGS(__VA_ARGS__),__VA_ARGS__)\
        }

/**
 * \def ORM_REGISTER_AND_CONSTRUCT(klass,colum,...)
 * construct and register the class
 */

/**
 * \brief construct and register the class
 * \param klass the class name
 * \param colum the table name in the db
 * \param ... is like this (attr name,attr colum name)
 * \note this macro have to be use out of any namespace
 * \code
class Spell : public orm::SqlObject<Spell>
{
    public:
        Spell();
        orm::CharField<255> name;
        orm::IntegerField element;

        ORM_MAKE_STATIC_COLUMN(name,element);

};
ORM_REGISTER_AND_CONSTRUCT(Spell,"spell",name,"name",element,"element")

 * \endcode
 */
#define ORM_REGISTER_AND_CONSTRUCT(klass,column,...) \
        ORM_REGISTER(klass,column,__VA_ARGS__)\
        ORM_MAKE_CONSTRUCTOR(::,klass,__VA_ARGS__)

/**
 * \brief construct and register the class
 * \param NAMESPACE the namspace of the class
 * \param klass the class name
 * \param colum the table name in the db
 * \param ... is like this (attr name,attr colum name)
 * \note this macro have to be use out of any namespace
 * \code
namespace a
{
    class TestNamespace : public orm::SqlObject<TestNamespace>
    {
        public:
        TestNamespace();
        orm::CharField<255> name;

        ORM_MAKE_STATIC_COLUMN(name);

    };
}
ORM_REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(a,TestNamespace,"TestNamespace",name,"name") // out of namespace
\endcode

 */
#define ORM_REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(NAMESPACE,klass,column,...) \
        ORM_REGISTER(NAMESPACE::klass,column,__VA_ARGS__)\
        ORM_MAKE_CONSTRUCTOR(NAMESPACE::,klass,__VA_ARGS__)

/******************************************
 ********** for ManyToMany ****************
 *****************************************/

#define ORM_M2M_REGISTER(klass,m2m,T_linked,table_name,owner_column,linked_column) \
    template<> const std::string orm::ManyToMany<klass,T_linked>::_table = table_name;\
    template<> const std::string orm::ManyToMany<klass,T_linked>::ORM_MAKE_NAME(_owner) = owner_column;\
    template<> const std::string orm::ManyToMany<klass,T_linked>::ORM_MAKE_NAME(_linked) = linked_column;\
    template<> const std::string orm::ManyToMany<klass,T_linked>::ORM_MAKE_NAME(_related) = JOIN_ALIAS(table_name,linked_column);\
    template<> orm::DB* orm::ManyToMany<klass,T_linked>::defaultDBConnection = &orm::DB::Default;\
    template<> orm::M2MRegister<klass,T_linked> orm::ManyToMany<klass,T_linked>::_register = orm::M2MRegister<klass,T_linked>();


#endif //guard
