#include "ShlibInternal.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool WindowInit(WindowCreateInfo *pCreateInfo, Window **ppWindow)
{
    if (!glfwInit())
        return 0;

    Window *window = malloc(sizeof(Window));
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 0;

    *ppWindow = window;
    return 1;
}

void WindowFree(Window *pWindow)
{
    glfwDestroyWindow(pWindow->pHandle);
    free(pWindow);
}

bool ApplicationInit(AppCreateInfo *pCreateInfo, Application **ppApp)
{
    Window *window;

    WindowCreateInfo createInfo;
    createInfo.width = pCreateInfo->width;
    createInfo.height = pCreateInfo->height;
    createInfo.pTitle = pCreateInfo->pTitle;
    createInfo.glVersionMajor = 4;
    createInfo.glVersionMinor = 0;

    if (!WindowInit(&createInfo, &window))
        return 0;

    Application *app = malloc(sizeof(Application));
    app->pWindow = window;
    app->pUpdateFunction = pCreateInfo->pUpdateFunction;

    *ppApp = app;
    return 1;
}

void ApplicationFree(Application *pApp)
{
    WindowFree(pApp->pWindow);
    free(pApp);
}

void ApplicationRun(Application *pApp)
{
    glClearColor(0, 0, 0, 1);

    float start = (float)glfwGetTime();
    float end = start;
    float delta;

    while(!glfwWindowShouldClose(pApp->pWindow->pHandle))
    {
        delta = end - start;
        start = (float)glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        if (pApp->pUpdateFunction)
            pApp->pUpdateFunction(delta);

        glfwPollEvents();
        glfwSwapBuffers(pApp->pWindow->pHandle);

        end = (float)glfwGetTime();
    }
}
