#ifndef SHLIB_PROGRAM_H
#define SHLIB_PROGRAM_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

#include "Vector.h"
#include "Matrix.h"

struct sProgramCreateInfo {
    const char *pVertexSource;
    const char *pFragmentSource;
    const char *pGeometrySource;
    const char *pTessControlSource;
    const char *pTessEvaluationSource;
};

struct sProgramComputeCreateInfo
{
    const char *pComputeSource;
};

struct sProgram {
    unsigned int programID;
};

typedef struct sProgramCreateInfo ProgramCreateInfo;
typedef struct sProgramComputeCreateInfo ProgramComputeCreateInfo;
typedef struct sProgram *Program;

bool ProgramCreate(ProgramCreateInfo *pCreateInfo, Program *pProgram);

bool ProgramCreateCompute(ProgramComputeCreateInfo *pCreateInfo, Program *pProgram);

void ProgramDestroy(Program program);

void ProgramUse(Program program);

void ProgramDispatch(Program program, int x, int y, int z);

int ProgramUniformLocation(Program program, const char *pName);

void ProgramUploadBool(Program program, int location, bool value);

void ProgramUploadInt(Program program, int location, int value);

void ProgramUploadIntArray(Program program, int location, int *values, int count);

void ProgramUploadFloat(Program program, int location, float value);

void ProgramUploadFloatArray(Program program, int location, float *values, int count);

void ProgramUploadVec2(Program program, int location, Vec2 value);

void ProgramUploadVec3(Program program, int location, Vec3 value);

void ProgramUploadVec4(Program program, int location, Vec4 value);

void ProgramUploadMatrix(Program program, int location, Matrix value);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_PROGRAM_H
