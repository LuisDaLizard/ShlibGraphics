//
// Created by Luis on 3/11/2024.
//

#ifndef SHLIB_WINDOW_H
#define SHLIB_WINDOW_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

struct sWindowCreateInfo {
    char glVersionMajor;
    char glVersionMinor;
    int width;
    int height;
    const char *pTitle;
};

struct sWindow {
    int width;
    int height;
    void *pHandle;
};

typedef struct sWindowCreateInfo WindowCreateInfo;
typedef struct sWindow *Window;

bool WindowInit(WindowCreateInfo *pCreateInfo, Window *pWindow);

void WindowFree(Window window);

bool WindowShouldClose(Window window);

void WindowPollEvents(Window window);

void WindowSwapBuffers(Window window);

void WindowSetVSync(Window window, bool vsync);

void WindowSetFullscreen(Window window, bool fullscreen);

void WindowSetClearColor(float r, float g, float b);

void WindowClear();

void WindowClearDepth();

#ifdef __cplusplus
}
#endif

#endif //SHLIB_WINDOW_H
