set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM/models)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM/models)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/SqlObject.hpp
    ${INCROOT}/SqlObject.tpl
    ${INCROOT}/SqlObjectBase.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/SqlObjectBase.cpp
)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
