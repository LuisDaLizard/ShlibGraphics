#ifndef SHLIBINTERNAL_H
#define SHLIBINTERNAL_H

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct sVec2
{
    float x, y;
} Vec2;

typedef struct sVec3
{
    float x, y, z;
} Vec3;

typedef struct sVec4
{
    float x, y, z, w;
} Vec4;

typedef struct sMatrix
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} Matrix;

typedef struct sWindowCreateInfo
{
    char glVersionMajor;
    char glVersionMinor;
    int width;
    int height;
    const char *pTitle;
} WindowCreateInfo;

typedef struct sWindow
{
    int width;
    int height;
    void *pHandle;
} Window;

typedef void (*UpdateFunc)(float);

typedef struct sAppCreateInfo
{
    int width;
    int height;
    const char *pTitle;
    UpdateFunc pUpdateFunction;
    void *pData;
} AppCreateInfo;

typedef struct sApplication
{
    Window *pWindow;
    UpdateFunc pUpdateFunction;
    void *pData;
} Application;

bool WindowInit(WindowCreateInfo *pCreateInfo, Window **ppWindow);
void WindowFree(Window *pWindow);

bool ApplicationInit(AppCreateInfo *pCreateInfo, Application **ppApp);
void ApplicationFree(Application *pApp);
void ApplicationRun(Application *pApp);

char *FileReadText(const char *filePath);
void *FileReadBytes(const char *filePath, int *size);
void FileFree(void *contents);

void MatrixPrint(Matrix matrix);
void Vec3Print(Vec3 vector);
Matrix MatrixIdentity(void);
Matrix MatrixMul(Matrix left, Matrix right);
Vec3 MatrixMulVec3(Matrix left, Vec3 right);
Vec4 MatrixMulVec4(Matrix left, Vec4 right);

Vec3 Vec3Add(Vec3 left, Vec3 right);
Vec3 Vec3Sub(Vec3 left, Vec3 right);
float Vec3Dot(Vec3 left, Vec3 right);
Vec3 Vec3Normalize(Vec3 vector);
Vec3 Vec3Cross(Vec3 left, Vec3 right);
Vec3 Vec3Negate(Vec3 vector);
Vec3 Vec3Scale(Vec3 vector, float scalar);
Vec3 Vec3Mul(Vec3 left, Vec3 right);
float Vec3Magnitude(Vec3 vector);

Matrix MatrixCreateScale(Vec3 scale);
Matrix MatrixCreateUScale(float scale);
Matrix MatrixCreateTranslation(Vec3 translation);
Matrix MatrixScale(Matrix matrix, Vec3 scale);
Matrix MatrixUScale(Matrix matrix, float scale);
Matrix MatrixTranslate(Matrix matrix, Vec3 translation);
// TODO: Rotation


#endif //SHLIBINTERNAL_H
