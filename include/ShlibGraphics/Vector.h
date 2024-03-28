#ifndef SHLIB_VECTOR_H
#define SHLIB_VECTOR_H

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#endif

#include "math.h"

typedef struct sVec2 {
    float x, y;
} Vec2;

typedef struct sVec3 {
    float x, y, z;
} Vec3;

typedef struct sVec4 {
    float x, y, z, w;
} Vec4;

void Vec3Print(Vec3 vector);

inline Vec3 Vec3Add(Vec3 left, Vec3 right);

inline Vec3 Vec3Sub(Vec3 left, Vec3 right);

inline float Vec3Dot(Vec3 left, Vec3 right);

inline Vec3 Vec3Normalize(Vec3 vector);

inline Vec3 Vec3Cross(Vec3 left, Vec3 right);

inline Vec3 Vec3Negate(Vec3 vector);

inline Vec3 Vec3Scale(Vec3 vector, float scalar);

inline Vec3 Vec3Mul(Vec3 left, Vec3 right);

inline float Vec3Magnitude(Vec3 vector);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_VECTOR_H
