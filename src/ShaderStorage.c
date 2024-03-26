#include "ShlibGraphics/ShaderStorage.h"

#include <glad/glad.h>
#include <stdlib.h>

bool ShaderStorageCreate(ShaderStorageCreateInfo *pCreateInfo, ShaderStorage *pShaderStorage)
{
    if (!pCreateInfo || !pShaderStorage)
        return false;

    if (pCreateInfo->maxSize <= 0)
        return false;

    unsigned int id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);

    glBufferData(GL_SHADER_STORAGE_BUFFER, pCreateInfo->maxSize, pCreateInfo->pData, (pCreateInfo->isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    ShaderStorage result = malloc(sizeof(struct sShaderStorage));
    result->maxSize = pCreateInfo->maxSize;
    result->bufferID = id;

    *pShaderStorage = result;
    return true;
}

void ShaderStorageDestroy(ShaderStorage storage)
{
    glDeleteBuffers(1, &storage->bufferID);
    free(storage);
}

void ShaderStorageSetData(ShaderStorage storage, int offset, int size, void *pData)
{
    if (offset < 0 || size < 0)
        return;

    if (offset + size > storage->maxSize)
        return;

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, storage->bufferID);

    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, pData);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBind(ShaderStorage storage, int location)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, location, storage->bufferID);
}