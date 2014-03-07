set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM/core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM/core)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Cache.hpp
    ${INCROOT}/Cache.tpl
    ${INCROOT}/macros.hpp
    ${INCROOT}/Register.hpp
    ${INCROOT}/Register.tpl
    ${INCROOT}/Tables.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/Tables.cpp
)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
