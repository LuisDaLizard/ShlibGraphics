#include "ShlibGraphics/UniformBuffer.h"

#include <glad/glad.h>
#include <stdlib.h>

bool UniformBufferCreate(UniformBufferCreateInfo *pCreateInfo, UniformBuffer *pUniformBuffer)
{
    if (!pCreateInfo || !pUniformBuffer)
        return false;

    if (pCreateInfo->size <= 0)
        return false;

    unsigned int id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_UNIFORM_BUFFER, id);

    glBufferData(GL_UNIFORM_BUFFER, pCreateInfo->size, pCreateInfo->pData, (pCreateInfo->isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    UniformBuffer result = malloc(sizeof(struct sUniformBuffer));
    result->maxSize = pCreateInfo->size;
    result->bufferID = id;

    *pUniformBuffer = result;
    return true;
}

void UniformBufferDestroy(UniformBuffer uniform)
{
    glDeleteBuffers(1, &uniform->bufferID);
    free(uniform);
}

void UniformBufferSetData(UniformBuffer uniform, int offset, int size, void *pData)
{
    if (offset < 0 || size < 0)
        return;

    if (offset + size > uniform->maxSize)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, uniform->bufferID);

    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, pData);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferBindToProgram(UniformBuffer uniform, Program program, const char *pName, int location)
{
    glBindBuffer(GL_UNIFORM_BUFFER, uniform->bufferID);

    glUniformBlockBinding(program->programID, glGetUniformBlockIndex(program->programID, pName), location);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferBind(UniformBuffer uniform, int location)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, location, uniform->bufferID);
}