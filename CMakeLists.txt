cmake_minimum_required (VERSION 2.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# project name
project (ORM)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 4)
set(VERSION_PATCH 0)


# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# add an option for choosing the build type (shared or static)
#set_option(BUILD_SHARED_LIBS FALSE BOOL "TRUE to build as shared libraries, FALSE to build it as static libraries")

# add an option for building the examples
set_option(BUILD_EXAMPLES TRUE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

set_option(BUILD_SUPPORT_SQLITE3 TRUE BOOL "TRUE to build support for sqlite3 backends, FALSE to ignore them")

set_option(BUILD_SUPPORT_MYSQL FALSE BOOL "TRUE to build support for Mysql backends, FALSE to ignore them")


#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")

set(DEFINES "")

if(BUILD_SUPPORT_SQLITE3)
	if(UNIX)
		find_library(LIB_PTHREAD pthread)
		set(LIBS ${LIBS} ${LIB_PTHREAD})
	endif()
	set(DEFINES "${DEFINES} -DSQLITE_OMIT_LOAD_EXTENSION")
endif()

if(BUILD_SUPPORT_MYSQL)
	find_library(LIB_MYSQL mysqlcppconn)
	set(LIBS ${LIBS} ${LIB_MYSQL})
endif()

set(WARNING "-Wall")
set(FLAGS "-o3")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)

# add the subdirectories
add_subdirectory(src/ORM)
#build exemples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
    #add_executable(toDo main.cc)

endif()
#build doc
if(BUILD_DOC)
    add_subdirectory(doc)
endif()

