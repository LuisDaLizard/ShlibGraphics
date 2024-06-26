cmake_minimum_required(VERSION 3.23)
project(ShlibGraphics C)

# CMAKE OPTIONS #
option(BUILD_EXAMPLES "Build all example projects" ON)

# PROJECT SUBDIRECTORIES #
add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)

# PROJECT SETTINGS #
set(CMAKE_C_STANDARD 90)

set(SHLIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
        src/Matrix.c
        src/Vector.c
        src/Utils.c
        src/Window.c
        src/Program.c
        src/Mesh.c
        src/Texture.c
        src/Framebuffer.c
        src/Graphics.c
        src/ShaderStorage.c
        src/UniformBuffer.c)

set(INCLUDES
        include
        libs/glfw/include
        libs/glad/include )

set(LIBS
        glfw
        glad )

set(DEFINITIONS )

# PLATFORM SPECIFIC SETTINGS #
if(APPLE)

    set(LIBS ${LIBS}
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            )

    set(DEFINITIONS ${DEFINITIONS}
            -DGL_SILENCE_DEPRECATION
            )

elseif(WIN32)

    set(LIBS ${LIBS}
            opengl32.lib
            )

endif()

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()