cmake_minimum_required(VERSION 3.23)
project(03-Texture C)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ShlibGraphics)
target_include_directories(${PROJECT_NAME} PRIVATE ${SHLIB_INCLUDE})