#ifndef SHLIB_UNIFORM_BUFFER_H
#define SHLIB_UNIFORM_BUFFER_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

#include "Program.h"

struct sUniformBufferCreateInfo
{
    bool isStatic;
    int size;
    void *pData;
};

struct sUniformBuffer
{
    unsigned int bufferID;
    int maxSize;
};

typedef struct sUniformBufferCreateInfo UniformBufferCreateInfo;
typedef struct sUniformBuffer *UniformBuffer;

bool UniformBufferCreate(UniformBufferCreateInfo *pCreateInfo, UniformBuffer *pUniformBuffer);
void UniformBufferDestroy(UniformBuffer uniform);

void UniformBufferSetData(UniformBuffer uniform, int offset, int size, void *pData);
void UniformBufferBindToProgram(UniformBuffer uniform, Program program, const char *pName, int location);
void UniformBufferBind(UniformBuffer uniform, int location);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_UNIFORM_BUFFER_H
