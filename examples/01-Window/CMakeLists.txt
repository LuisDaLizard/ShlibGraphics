cmake_minimum_required(VERSION 3.23)
project(01-Window C)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} Shlib)
target_include_directories(${PROJECT_NAME} PRIVATE ${SHLIB_INCLUDE})