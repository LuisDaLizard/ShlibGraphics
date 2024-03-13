#ifndef SHLIB_UTILS_H
#define SHLIB_UTILS_H

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <math.h>
#include <stdbool.h>

#define DEG2RADF (float)(M_PI / 180.0f)
#define RAD2DEGF (float)(180.0f / M_PI)

void WriteInfo(const char *message);
void WriteWarning(const char *message);
void WriteError(int code, const char *message);

char *FileReadText(const char *filePath);
void *FileReadBytes(const char *filePath, int *size);
void FileFree(void *contents);
bool CheckGLErrors();

#endif //SHLIB_UTILS_H
