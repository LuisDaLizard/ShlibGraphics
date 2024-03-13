#include "Program.h"

#include <glad/glad.h>
#include <stdlib.h>

bool ProgramCreate(ProgramCreateInfo *pCreateInfo, Program *pProgram) {
    if (!pCreateInfo->pVertexSource || !pCreateInfo->pFragmentSource)
        return false;

    unsigned int id;
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &pCreateInfo->pVertexSource, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        //TODO: Log Error
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &pCreateInfo->pFragmentSource, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        //TODO: Log Error
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        //TODO: Log Error
        return false;
    }

    Program program = malloc(sizeof(struct sProgram));

    program->programID = id;

    *pProgram = program;
    return true;
}

void ProgramDestroy(Program program)
{
    glDeleteProgram(program->programID);
    free(program);
}

void ProgramUse(Program program)
{
    glUseProgram(program->programID);
}

int ProgramUniformLocation(Program program, const char *pName)
{
    return glGetUniformLocation(program->programID, pName);
}

void ProgramUploadBool(Program program, int location, bool value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform1i(location, value);
}

void ProgramUploadInt(Program program, int location, int value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform1i(location, value);
}

void ProgramUploadIntArray(Program program, int location, int *values, int count)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform1iv(location, count, values);
}

void ProgramUploadFloat(Program program, int location, float value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform1f(location, value);
}

void ProgramUploadFloatArray(Program program, int location, float *values, int count)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform1fv(location, count, values);
}

void ProgramUploadVec2(Program program, int location, Vec2 value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform2f(location, value.x, value.y);
}

void ProgramUploadVec3(Program program, int location, Vec3 value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform3f(location, value.x, value.y, value.z);
}

void ProgramUploadVec4(Program program, int location, Vec4 value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ProgramUploadMatrix(Program program, int location, Matrix value)
{
    if (location < 0)
        return;

    ProgramUse(program);
    glUniformMatrix4fv(location, 1, GL_TRUE, (float *)&value);
}