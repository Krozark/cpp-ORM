#ifndef ORM_DEBUG_HPP
#define ORM_DEBUG_HPP

#define DEFAULT_MAX_DEPTH 1

#define DEGUG_NO 0
#define DEBUG_SQL 1<<1
#define DEBUG_REGISTER 1<<2

#define DEBUG (DEBUG_SQL | DEBUG_REGISTER)

#if DEBUG > 0
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
