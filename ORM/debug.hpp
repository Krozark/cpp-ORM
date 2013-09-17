#ifndef ORM_DEBUG_HPP
#define ORM_DEBUG_HPP

#define ORM_DEFAULT_MAX_DEPTH 1

#define ORM_ALLOW_EXCEPTION 0

#define ORM_DEGUG_NO 0
#define ORM_DEBUG_SQL 1<<1
#define ORM_DEBUG_REGISTER 1<<2
#define ORM_DEBUG_GET_OBJ 1<<3
#define ORM_DEBUG_GET_ATTR 1<<4

#define ORM_DEBUG_FULL (ORM_DEBUG_SQL)

//#define ORM_DEBUG (ORM_DEBUG_SQL | ORM_DEBUG_REGISTER)
#define ORM_DEBUG (ORM_DEBUG_FULL)

#if ORM_DEBUG > 0
#include <iostream>
#endif


/**************************
******** COLORS ***********
**************************/


#define ROUGE  	"\033[31m"
#define VERT   	"\033[32m"
#define JAUNE  	"\033[33m"
#define BLEU   	"\033[34m"
#define MAGENTA "\033[35m"
#define LMAGENTA "\033[01;35m"
#define BLEU2 "\033[36m"
#define COMMENTAIRE "\033[31m"
#define BLANC 	"\033[00m"

#endif
