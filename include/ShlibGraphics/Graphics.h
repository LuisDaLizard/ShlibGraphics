#ifndef SHLIB_GRAPHICS_H
#define SHLIB_GRAPHICS_H

#ifdef __cplusplus
extern "C"{
#endif

void GLClearColor(float r, float g, float b, float a);

void GLClear();

void GLClearDepth();

#ifdef __cplusplus
}
#endif

#endif //SHLIB_GRAPHICS_H
