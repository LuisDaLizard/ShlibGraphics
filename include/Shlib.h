#ifndef SHLIBENGINE_SHLIB_H
#define SHLIBENGINE_SHLIB_H

#include <stdbool.h>

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

/**
 * Creates an OpenGL window using the creation info structure
 *
 * @param pCreateInfo - Window creation info which contains settings for window creation
 * @param ppWindow - Contains the created OpenGL window if function exits successfully
 * @return Whether an OpenGL window was created
 */
extern bool WindowInit(WindowCreateInfo *pCreateInfo, Window **ppWindow);

/**
 * Frees the memory allocated by an OpenGL window
 *
 * @param pWindow - Window to be destroyed
 */
extern void WindowFree(Window *pWindow);

extern bool ApplicationInit(AppCreateInfo *pCreateInfo, Application **ppApp);
extern void ApplicationFree(Application *pApp);
extern void ApplicationRun(Application *pApp);

extern char *FileReadText(const char *filePath);
extern void *FileReadBytes(const char *filePath, int *size);
extern void FileFree(void *contents);

extern void MatrixPrint(Matrix matrix);
extern void Vec3Print(Vec3 vector);
extern Matrix MatrixIdentity(void);
extern Matrix MatrixMul(Matrix left, Matrix right);
extern Vec3 MatrixMulVec3(Matrix left, Vec3 right);
extern Vec4 MatrixMulVec4(Matrix left, Vec4 right);

extern Vec3 Vec3Add(Vec3 left, Vec3 right);
extern Vec3 Vec3Sub(Vec3 left, Vec3 right);
extern float Vec3Dot(Vec3 left, Vec3 right);
extern Vec3 Vec3Normalize(Vec3 vector);
extern Vec3 Vec3Cross(Vec3 left, Vec3 right);
extern Vec3 Vec3Negate(Vec3 vector);
extern Vec3 Vec3Scale(Vec3 vector, float scalar);
extern Vec3 Vec3Mul(Vec3 left, Vec3 right);
extern float Vec3Magnitude(Vec3 vector);

extern Matrix MatrixCreateScale(Vec3 scale);
extern Matrix MatrixCreateUScale(float scale);
extern Matrix MatrixCreateTranslation(Vec3 translation);
extern Matrix MatrixScale(Matrix matrix, Vec3 scale);
extern Matrix MatrixUScale(Matrix matrix, float scale);
extern Matrix MatrixTranslate(Matrix matrix, Vec3 translation);

#endif //SHLIBENGINE_SHLIB_H
