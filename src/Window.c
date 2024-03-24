//
// Created by Luis on 3/11/2024.
//

#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

void WindowResizeCallback(GLFWwindow *handle, int width, int height);

bool WindowInit(WindowCreateInfo *pCreateInfo, Window *pWindow)
{
    if (!glfwInit())
        return 0;

    Window window = malloc(sizeof(struct sWindow));
    window->width = pCreateInfo->width;
    window->height = pCreateInfo->height;
    window->pHandle = NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, pCreateInfo->glVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, pCreateInfo->glVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window->pHandle = glfwCreateWindow(window->width, window->height, pCreateInfo->pTitle, NULL, NULL);

    if (!window->pHandle)
        return 0;

    glfwMakeContextCurrent(window->pHandle);
    glfwSwapInterval(0);
    glfwSetWindowUserPointer(window->pHandle, window);
    glfwSetFramebufferSizeCallback(window->pHandle, WindowResizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 0;

    *pWindow = window;
    return 1;
}

void WindowFree(Window window)
{
    glfwDestroyWindow(window->pHandle);
    free(window);
}

bool WindowShouldClose(Window window)
{
    return glfwWindowShouldClose(window->pHandle);
}

void WindowPollEvents(Window window)
{
    glfwPollEvents();
}

void WindowSwapBuffers(Window window)
{
    glfwSwapBuffers(window->pHandle);
}

void WindowSetVSync(Window window, bool vsync)
{
    glfwSwapInterval(vsync);
}

void WindowSetFullscreen(Window window, bool fullscreen)
{
    glfwGetWindowMonitor(window->pHandle);
}

void WindowSetClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1);
}

void WindowClear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowClearDepth()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

bool WindowIsKeyDown(Window window, KeyCode key)
{
    return glfwGetKey(window->pHandle, key);
}

bool WindowIsMouseButtonDown(Window window, MouseButton button)
{
    return glfwGetMouseButton(window->pHandle, GLFW_MOUSE_BUTTON_MIDDLE);
}

void WindowGetMousePos(Window window, float *x, float *y)
{
    double xPos, yPos;
    glfwGetCursorPos(window->pHandle, &xPos, &yPos);

    *x = (float)xPos;
    *y = (float)yPos;
}


void WindowResizeCallback(GLFWwindow *handle, int width, int height)
{
    Window window = (Window) glfwGetWindowUserPointer(handle);
    if (!window)
        return;

    window->width = width;
    window->height = height;
}