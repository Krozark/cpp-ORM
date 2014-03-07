set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM/backends/Sqlite3)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM/backends/Sqlite3)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Sqlite3Bdd/hpp
    ${INCROOT}/Sqlite3Query.hpp
    ${INCROOT}/Sqlite3TableCreator.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/Sqlite3Bdd.cpp
    ${SRCROOT}/Sqlite3Query.cpp
    ${SRCROOT}/Sqlite3TableCreator.cpp
)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
