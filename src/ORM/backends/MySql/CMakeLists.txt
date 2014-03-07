set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM/backends/MySql)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM/backends/MySql)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/MySqlBdd.hpp
    ${INCROOT}/MySqlQuery.hpp
    ${INCROOT}/MySqlTableCreator.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/MySqlBdd.cpp
    ${SRCROOT}/MySqlQuery.cpp
    ${SRCROOT}/MySqlTableCreator.cpp
)
# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
