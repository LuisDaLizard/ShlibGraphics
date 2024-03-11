#include "ShlibInternal.h"

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdio.h>

#define DEG2RAD (float)(M_PI / 180.0f)
#define RAD2DEG (float)(180.0f / M_PI)

void MatrixPrint(Matrix matrix)
{
    printf("|%f, %f, %f, %f|\n", matrix.m00, matrix.m01, matrix.m02, matrix.m03);
    printf("|%f, %f, %f, %f|\n", matrix.m10, matrix.m11, matrix.m12, matrix.m13);
    printf("|%f, %f, %f, %f|\n", matrix.m20, matrix.m21, matrix.m22, matrix.m23);
    printf("|%f, %f, %f, %f|\n", matrix.m30, matrix.m31, matrix.m32, matrix.m33);
}

void Vec3Print(Vec3 vector)
{
    printf("(%f, %f, %f)\n", vector.x, vector.y, vector.z);
}

Matrix MatrixIdentity(void)
{
    Matrix result = { 0 };

    result.m00 = 1;
    result.m11 = 1;
    result.m22 = 1;
    result.m33 = 1;

    return result;
}

Matrix MatrixMul(Matrix left, Matrix right)
{
    Matrix result;

    result.m00 = left.m00 * right.m00 + left.m01 * right.m10 + left.m02 * right.m20 + left.m03 * right.m30;
    result.m01 = left.m00 * right.m01 + left.m01 * right.m11 + left.m02 * right.m21 + left.m03 * right.m31;
    result.m02 = left.m00 * right.m02 + left.m01 * right.m12 + left.m02 * right.m22 + left.m03 * right.m32;
    result.m03 = left.m00 * right.m03 + left.m01 * right.m13 + left.m02 * right.m23 + left.m03 * right.m33;

    result.m10 = left.m10 * right.m00 + left.m11 * right.m10 + left.m12 * right.m20 + left.m13 * right.m30;
    result.m11 = left.m10 * right.m01 + left.m11 * right.m11 + left.m12 * right.m21 + left.m13 * right.m31;
    result.m12 = left.m10 * right.m02 + left.m11 * right.m12 + left.m12 * right.m22 + left.m13 * right.m32;
    result.m13 = left.m10 * right.m03 + left.m11 * right.m13 + left.m12 * right.m23 + left.m13 * right.m33;

    result.m20 = left.m20 * right.m00 + left.m21 * right.m10 + left.m22 * right.m20 + left.m23 * right.m30;
    result.m21 = left.m20 * right.m01 + left.m21 * right.m11 + left.m22 * right.m21 + left.m23 * right.m31;
    result.m22 = left.m20 * right.m02 + left.m21 * right.m12 + left.m22 * right.m22 + left.m23 * right.m32;
    result.m23 = left.m20 * right.m03 + left.m21 * right.m13 + left.m22 * right.m23 + left.m23 * right.m33;

    result.m30 = left.m30 * right.m00 + left.m31 * right.m10 + left.m32 * right.m20 + left.m33 * right.m30;
    result.m31 = left.m30 * right.m01 + left.m31 * right.m11 + left.m32 * right.m21 + left.m33 * right.m31;
    result.m32 = left.m30 * right.m02 + left.m31 * right.m12 + left.m32 * right.m22 + left.m33 * right.m32;
    result.m33 = left.m30 * right.m03 + left.m31 * right.m13 + left.m32 * right.m23 + left.m33 * right.m33;

    return result;
}

Vec3 MatrixMulVec3(Matrix left, Vec3 right)
{
    Vec3 result;

    result.x = left.m00 * right.x + left.m01 * right.y + left.m02 * right.z + left.m03;
    result.y = left.m10 * right.x + left.m11 * right.y + left.m12 * right.z + left.m13;
    result.z = left.m20 * right.x + left.m21 * right.y + left.m22 * right.z + left.m23;

    return result;
}

Vec4 MatrixMulVec4(Matrix left, Vec4 right)
{
    Vec4 result;

    result.x = left.m00 * right.x + left.m01 * right.y + left.m02 * right.z + left.m03 * right.w;
    result.y = left.m10 * right.x + left.m11 * right.y + left.m12 * right.z + left.m13 * right.w;
    result.z = left.m20 * right.x + left.m21 * right.y + left.m22 * right.z + left.m23 * right.w;
    result.w = left.m30 * right.x + left.m31 * right.y + left.m32 * right.z + left.m33 * right.w;

    return result;
}

Vec3 Vec3Add(Vec3 left, Vec3 right)
{
    Vec3 result;

    result.x = left.x + right.x;
    result.y = left.y + right.y;
    result.z = left.z + right.z;

    return result;
}

Vec3 Vec3Sub(Vec3 left, Vec3 right)
{
    Vec3 result;

    result.x = left.x - right.x;
    result.y = left.y - right.y;
    result.z = left.z - right.z;

    return result;
}
float Vec3Dot(Vec3 left, Vec3 right)
{
    float result;

    result = left.x * right.x + left.y * right.y + left.z * right.z;

    return result;
}

Vec3 Vec3Normalize(Vec3 vector)
{
    float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

    if (magnitude == 0)
        return (Vec3){ 0, 0, 0 };

    float invMagnitude = 1 / magnitude;

    vector.x *= invMagnitude;
    vector.y *= invMagnitude;
    vector.z *= invMagnitude;

    return vector;
}

Vec3 Vec3Cross(Vec3 left, Vec3 right)
{
    Vec3 result;

    result.x = left.y * right.z - left.z * right.y;
    result.y = left.z * right.x - left.x * right.z;
    result.z = left.x * right.y - left.y * right.x;

    return result;
}

Vec3 Vec3Negate(Vec3 vector)
{
    Vec3 result;

    result.x = -vector.x;
    result.y = -vector.y;
    result.z = -vector.z;

    return result;
}

Vec3 Vec3Scale(Vec3 vector, float scalar)
{
    Vec3 result;

    result.x = vector.x * scalar;
    result.y = vector.y * scalar;
    result.z = vector.z * scalar;

    return result;
}

Vec3 Vec3Mul(Vec3 left, Vec3 right)
{
    Vec3 result;

    result.x = left.x * right.x;
    result.y = left.y * right.y;
    result.z = left.z * right.z;

    return result;
}

float Vec3Magnitude(Vec3 vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Matrix MatrixCreateScale(Vec3 scale)
{
    Matrix result = MatrixIdentity();

    result.m00 *= scale.x;
    result.m11 *= scale.y;
    result.m22 *= scale.z;

    return result;
}

Matrix MatrixCreateUScale(float scale)
{
    Matrix result = MatrixIdentity();

    result.m00 *= scale;
    result.m11 *= scale;
    result.m22 *= scale;

    return result;
}

Matrix MatrixCreateTranslation(Vec3 translation)
{
    Matrix result = MatrixIdentity();

    result.m03 = translation.x;
    result.m13 = translation.y;
    result.m23 = translation.z;

    return result;
}

Matrix MatrixScale(Matrix matrix, Vec3 scale)
{
    return MatrixMul(matrix, MatrixCreateScale(scale));
}

Matrix MatrixUScale(Matrix matrix, float scale)
{
    return MatrixMul(matrix, MatrixCreateUScale(scale));
}

Matrix MatrixTranslate(Matrix matrix, Vec3 translation)
{
    return MatrixMul(matrix, MatrixCreateTranslation(translation));
}