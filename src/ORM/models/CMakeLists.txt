set(INCROOT ${INCROOT}/models)
set(SRCROOT ${SRCROOT}/models)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/SqlObject.hpp
    ${INCROOT}/SqlObject.tpl
    ${INCROOT}/SqlExtends.hpp
    ${INCROOT}/SqlExtends.tpl
    ${INCROOT}/SqlObjectBase.hpp
)


list(APPEND FILES_SRC
    ${SRCROOT}/SqlObjectBase.cpp
)

# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
