set(INCROOT ${PROJECT_SOURCE_DIR}/examples)
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples)

find_library(LIBS mysqlcppconn sqlite3 pthread orm)

add_executable(basic main.cpp)
target_link_libraries(basic ${LIBS})


