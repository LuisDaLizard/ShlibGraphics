#ifndef SHLIB_SHADERSTORAGE_H
#define SHLIB_SHADERSTORAGE_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

struct sShaderStorageCreateInfo {
    bool isStatic;
    int maxSize;
    void *pData;
};

struct sShaderStorage {
    unsigned int bufferID;
    int maxSize;
};

typedef struct sShaderStorageCreateInfo ShaderStorageCreateInfo;
typedef struct sShaderStorage *ShaderStorage;

bool ShaderStorageCreate(ShaderStorageCreateInfo *pCreateInfo, ShaderStorage *pShaderStorage);

void ShaderStorageDestroy(ShaderStorage storage);

void ShaderStorageSetData(ShaderStorage storage, int offset, int size, void *pData);

void ShaderStorageBind(ShaderStorage storage, int location);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_SHADERSTORAGE_H
