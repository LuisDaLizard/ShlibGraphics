//
// Created by Luis on 3/11/2024.
//

#ifndef SHLIB_WINDOW_H
#define SHLIB_WINDOW_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef enum eKeyCode
{
    KEY_SPACE = 32,
    KEY_A = 65,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_RIGHT = 262,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
} KeyCode;

typedef enum eMouseButton
{
    MOUSE_LEFT = 0,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
} MouseButton;

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

bool WindowIsKeyDown(Window window, KeyCode key);

bool WindowIsMouseButtonDown(Window window, MouseButton button);

void WindowGetMousePos(Window window, float *x, float *y);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_WINDOW_H
