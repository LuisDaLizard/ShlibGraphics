#ifndef SHLIB_UTILS_H
#define SHLIB_UTILS_H

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <math.h>

#define DEG2RADF (float)(M_PI / 180.0f)
#define RAD2DEGF (float)(180.0f / M_PI)

char *FileReadText(const char *filePath);
void *FileReadBytes(const char *filePath, int *size);
void FileFree(void *contents);

#endif //SHLIB_UTILS_H
