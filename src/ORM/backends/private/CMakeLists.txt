set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM/backends/private)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM/backends/private)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Filter.hpp
    ${INCROOT}/Filter.tpl
    ${INCROOT}/M2MQuerySet.hpp
    ${INCROOT}/M2MQuerySet.tpl
    ${INCROOT}/QuerySet.hpp
    ${INCROOT}/QuerySet.tpl
    ${INCROOT}/TableCreator.hpp
    ${INCROOT}/VFilter.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/Filter.cpp
    ${SRCROOT}/TableCreator.cpp
    ${SRCROOT}/VFilter.cpp
)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
