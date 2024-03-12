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

typedef void (*InitFunc)();
typedef void (*UpdateFunc)(float);
typedef void (*DrawFunc)();
typedef void (*FreeFunc)();

typedef struct sAppCreateInfo
{
    int width;
    int height;
    const char *pTitle;
    InitFunc pInitFunction;
    UpdateFunc pUpdateFunction;
    DrawFunc pDrawFunction;
    FreeFunc pFreeFunction;
    void *pData;
} AppCreateInfo;

typedef struct sApplication
{
    Window *pWindow;
    InitFunc pInitFunction;
    UpdateFunc pUpdateFunction;
    DrawFunc pDrawFunction;
    FreeFunc pFreeFunction;
    void *pData;
} Application;

typedef struct sProgramCreateInfo
{
    const char *pVertexSource;
    const char *pFragmentSource;
} ProgramCreateInfo;

typedef struct sProgram
{
    unsigned int programID;
} Program;

typedef struct sMeshCreateInfo
{
    bool isStatic;
    int stride;
    int numVertices;
    float *pVertexData;
    int numAttributes;
    int *pAttributeComponents;
} MeshCreateInfo;

typedef struct sMesh
{
    unsigned int vao;
    unsigned int vbo;
    int numVertices;
} Mesh;

bool WindowInit(WindowCreateInfo *pCreateInfo, Window **ppWindow);
void WindowFree(Window *pWindow);

bool ApplicationInit(AppCreateInfo *pCreateInfo, Application **ppApp);
void ApplicationFree(Application *pApp);
void ApplicationRun(Application *pApp);

bool ProgramCreate(ProgramCreateInfo *pCreateInfo, Program **ppProgram);
void ProgramDestroy(Program *pProgram);
void ProgramUse(Program *pProgram);
int ProgramUniformLocation(Program *pProgram, const char *pName);
void ProgramUploadBool(Program *pProgram, int location, bool value);
void ProgramUploadInt(Program *pProgram, int location, int value);
void ProgramUploadIntArray(Program *pProgram, int location, int *values, int count);
void ProgramUploadFloat(Program *pProgram, int location, float value);
void ProgramUploadFloatArray(Program *pProgram, int location, float *values, int count);
void ProgramUploadVec2(Program *pProgram, int location, Vec2 value);
void ProgramUploadVec3(Program *pProgram, int location, Vec3 value);
void ProgramUploadVec4(Program *pProgram, int location, Vec4 value);
void ProgramUploadMatrix(Program *pProgram, int location, Matrix value);

bool MeshCreate(MeshCreateInfo *pCreateInfo, Mesh **ppMesh);
void MeshDestroy(Mesh *pMesh);
void MeshDraw(Mesh *pMesh);

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
