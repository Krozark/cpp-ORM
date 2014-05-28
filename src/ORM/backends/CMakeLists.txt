set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM/backends)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM/backends)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Bdd.hpp
    ${INCROOT}/Bdd.tpl
    ${INCROOT}/MySql.hpp
    ${INCROOT}/op.hpp
    ${INCROOT}/Query.hpp
    ${INCROOT}/Query.tpl
    ${INCROOT}/Sqlite3.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/Bdd.cpp
    ${SRCROOT}/op.cpp
    ${SRCROOT}/Query.cpp
)

add_subdirectory(MySql)
add_subdirectory(private)
add_subdirectory(Sqlite3)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
