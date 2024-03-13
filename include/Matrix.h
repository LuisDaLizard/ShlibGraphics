#ifndef SHLIB_MATH_H
#define SHLIB_MATH_H

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "math.h"

#include "Vector.h"

typedef struct sMatrix
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} Matrix;

void MatrixPrint(Matrix matrix);
Matrix MatrixIdentity(void);
Matrix MatrixMul(Matrix left, Matrix right);
Vec3 MatrixMulVec3(Matrix left, Vec3 right);
Vec4 MatrixMulVec4(Matrix left, Vec4 right);

Matrix MatrixCreateScale(Vec3 scale);
Matrix MatrixCreateUScale(float scale);
Matrix MatrixCreateTranslation(Vec3 translation);
Matrix MatrixScale(Matrix matrix, Vec3 scale);
Matrix MatrixUScale(Matrix matrix, float scale);
Matrix MatrixTranslate(Matrix matrix, Vec3 translation);

#endif //SHLIB_MATH_H
