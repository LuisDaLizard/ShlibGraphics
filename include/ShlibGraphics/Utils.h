#ifndef SHLIB_UTILS_H
#define SHLIB_UTILS_H

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <stdbool.h>

#define DEG2RADF (float)(M_PI / 180.0f)
#define RAD2DEGF (float)(180.0f / M_PI)
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)
#define CLAMP(min, a, max) (MAX(min, MIN(max, a)))

void WriteInfo(const char *message);

void WriteWarning(const char *message);

void WriteError(int code, const char *message);

char *FileReadText(const char *filePath);

void *FileReadBytes(const char *filePath, int *size);

void FileFree(void *contents);

bool CheckGLErrors();

double GetTime();

#ifdef __cplusplus
}
#endif

#endif //SHLIB_UTILS_H
