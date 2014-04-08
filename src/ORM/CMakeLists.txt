set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM)

set(FILES_HEADER
    ${INCROOT}/backends.hpp
    ${INCROOT}/debug.hpp
    ${INCROOT}/externals.hpp
    ${INCROOT}/fields.hpp
    ${INCROOT}/models.hpp
)
set(FILES_SRC)

add_subdirectory(backends)
add_subdirectory(core)
add_subdirectory(fields)
add_subdirectory(models)


#SHARED lib
add_library(orm SHARED ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(orm
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(orm ${LIBS})
INSTALL(TARGETS orm
    DESTINATION lib
)

#static lib
add_library(orm-static STATIC ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(orm-static
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(orm-static ${LIBS})
INSTALL(TARGETS orm-static
    DESTINATION lib
)

file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/include/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION include )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include )


########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)
add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
########################################################################

