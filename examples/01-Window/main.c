#include "ShlibGraphics/ShlibGraphics.h"
#include <stdio.h>

int main()
{
    Window window;
    WindowCreateInfo createInfo = { 0 };
    createInfo.glVersionMajor = 3;
    createInfo.glVersionMinor = 3;
    createInfo.width = 800;
    createInfo.height = 600;
    createInfo.pTitle = "01 - Window";

    if (!WindowInit(&createInfo, &window))
        return 1;

    GLClearColor(1, 1, 1, 1);

    while(!WindowShouldClose(window))
    {
        GLClear();

        WindowPollEvents(window);
        WindowSwapBuffers(window);
    }

    return 0;
}