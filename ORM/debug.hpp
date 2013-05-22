#ifndef ORM_DEBUG_HPP
#define ORM_DEBUG_HPP

#define DEGUG_NO 0
#define DEBUG_SQL 1<<1

#define DEBUG (DEBUG_SQL)

#if DEBUG > 0
#include <iostream>
#endif

#endif
