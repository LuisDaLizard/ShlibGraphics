#include "Graphics.h"
#include <glad/glad.h>

void GLClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void GLClear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLClearDepth()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}