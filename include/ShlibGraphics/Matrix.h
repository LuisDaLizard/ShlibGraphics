#ifndef SHLIB_MATH_H
#define SHLIB_MATH_H

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#endif

#include "math.h"

#include "Vector.h"

typedef struct sMatrix {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} Matrix;

void MatrixPrint(Matrix matrix);

inline Matrix MatrixIdentity(void);

inline Matrix MatrixMul(Matrix left, Matrix right);

inline Vec3 MatrixMulVec3(Matrix left, Vec3 right);

inline Vec4 MatrixMulVec4(Matrix left, Vec4 right);

inline Matrix MatrixCreateScale(Vec3 scale);

inline Matrix MatrixCreateUScale(float scale);

inline Matrix MatrixCreateTranslation(Vec3 translation);

inline Matrix MatrixScale(Matrix matrix, Vec3 scale);

inline Matrix MatrixUScale(Matrix matrix, float scale);

inline Matrix MatrixTranslate(Matrix matrix, Vec3 translation);

inline Matrix MatrixOrtho(float left, float right, float top, float bottom, float near, float far);

inline Matrix MatrixPerspective(float aspect, float fov, float near, float far);

inline Matrix MatrixLookAt(Vec3 eye, Vec3 target, Vec3 up);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_MATH_H
