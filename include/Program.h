#ifndef SHLIB_PROGRAM_H
#define SHLIB_PROGRAM_H

#include <stdbool.h>

#include "Vector.h"
#include "Matrix.h"

struct sProgramCreateInfo
{
    const char *pVertexSource;
    const char *pFragmentSource;
};

struct sProgram
{
    unsigned int programID;
};

typedef struct sProgramCreateInfo ProgramCreateInfo;
typedef struct sProgram *Program;

bool ProgramCreate(ProgramCreateInfo *pCreateInfo, Program *pProgram);
void ProgramDestroy(Program program);
void ProgramUse(Program program);
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

#endif //SHLIB_PROGRAM_H
