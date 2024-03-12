#include "ShlibInternal.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool WindowInit(WindowCreateInfo *pCreateInfo, Window **ppWindow)
{
    if (!glfwInit())
        return 0;

    Window *window = malloc(sizeof(Window));
    window->width = pCreateInfo->width;
    window->height = pCreateInfo->height;
    window->pHandle = NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, pCreateInfo->glVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, pCreateInfo->glVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window->pHandle = glfwCreateWindow(window->width, window->height, pCreateInfo->pTitle, NULL, NULL);

    if (!window->pHandle)
        return 0;

    glfwMakeContextCurrent(window->pHandle);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 0;

    *ppWindow = window;
    return 1;
}

void WindowFree(Window *pWindow)
{
    glfwDestroyWindow(pWindow->pHandle);
    free(pWindow);
}

bool ApplicationInit(AppCreateInfo *pCreateInfo, Application **ppApp)
{
    Window *window;

    WindowCreateInfo createInfo;
    createInfo.width = pCreateInfo->width;
    createInfo.height = pCreateInfo->height;
    createInfo.pTitle = pCreateInfo->pTitle;
    createInfo.glVersionMajor = 4;
    createInfo.glVersionMinor = 0;

    if (!WindowInit(&createInfo, &window))
        return 0;

    Application *app = malloc(sizeof(Application));
    app->pWindow = window;
    app->pInitFunction = pCreateInfo->pInitFunction;
    app->pUpdateFunction = pCreateInfo->pUpdateFunction;
    app->pDrawFunction = pCreateInfo->pDrawFunction;
    app->pFreeFunction = pCreateInfo->pFreeFunction;

    *ppApp = app;
    return 1;
}

void ApplicationFree(Application *pApp)
{
    WindowFree(pApp->pWindow);
    free(pApp);
}

void ApplicationRun(Application *pApp)
{
    glClearColor(0, 0, 0, 1);

    float start = (float)glfwGetTime();
    float end = start;
    float delta;

    if (pApp->pInitFunction)
        pApp->pInitFunction();

    while(!glfwWindowShouldClose(pApp->pWindow->pHandle))
    {
        delta = end - start;
        start = (float)glfwGetTime();

        if (pApp->pUpdateFunction)
            pApp->pUpdateFunction(delta);

        glClear(GL_COLOR_BUFFER_BIT);

        if (pApp->pDrawFunction)
            pApp->pDrawFunction();

        glfwPollEvents();
        glfwSwapBuffers(pApp->pWindow->pHandle);

        end = (float)glfwGetTime();
    }

    if (pApp->pFreeFunction)
        pApp->pFreeFunction();
}

bool ProgramCreate(ProgramCreateInfo *pCreateInfo, Program **ppProgram) {
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

    Program *program = malloc(sizeof(Program));

    program->programID = id;

    *ppProgram = program;
    return true;
}

void ProgramDestroy(Program *pProgram)
{
    glDeleteProgram(pProgram->programID);
    free(pProgram);
}

void ProgramUse(Program *pProgram)
{
    glUseProgram(pProgram->programID);
}

int ProgramUniformLocation(Program *pProgram, const char *pName)
{
    return glGetUniformLocation(pProgram->programID, pName);
}

void ProgramUploadBool(Program *pProgram, int location, bool value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform1i(location, value);
}

void ProgramUploadInt(Program *pProgram, int location, int value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform1i(location, value);
}

void ProgramUploadIntArray(Program *pProgram, int location, int *values, int count)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform1iv(location, count, values);
}

void ProgramUploadFloat(Program *pProgram, int location, float value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform1f(location, value);
}

void ProgramUploadFloatArray(Program *pProgram, int location, float *values, int count)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform1fv(location, count, values);
}

void ProgramUploadVec2(Program *pProgram, int location, Vec2 value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform2f(location, value.x, value.y);
}

void ProgramUploadVec3(Program *pProgram, int location, Vec3 value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform3f(location, value.x, value.y, value.z);
}

void ProgramUploadVec4(Program *pProgram, int location, Vec4 value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ProgramUploadMatrix(Program *pProgram, int location, Matrix value)
{
    if (location < 0)
        return;

    ProgramUse(pProgram);
    glUniformMatrix4fv(location, 1, GL_TRUE, (float *)&value);
}

bool MeshCreate(MeshCreateInfo *pCreateInfo, Mesh **ppMesh)
{
    if (!pCreateInfo)
        return false;

    if (pCreateInfo->stride <= 0 || pCreateInfo->numAttributes <= 0)
        return false;

    int i;
    int totalSize = 0;
    for (i = 0; i < pCreateInfo->numAttributes; i++)
    {
        if (pCreateInfo->pAttributeComponents[i] <= 0)
            return false;
        totalSize += pCreateInfo->pAttributeComponents[i] * sizeof(float);
    }

    if (totalSize != pCreateInfo->stride)
        return false;

    Mesh *mesh = malloc(sizeof(Mesh));
    mesh->numVertices = pCreateInfo->numVertices;

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);

    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, pCreateInfo->numVertices * pCreateInfo->stride, pCreateInfo->pVertexData, GL_STATIC_DRAW);

    int offset = 0;
    for (i = 0; i < pCreateInfo->numAttributes; i++)
    {
        int components = pCreateInfo->pAttributeComponents[i];

        glVertexAttribPointer(i, components, GL_FLOAT, GL_FALSE, pCreateInfo->stride, (void *) ((long long) offset));
        glEnableVertexAttribArray(i);

        offset += components * sizeof(float);
    }

    glBindVertexArray(0);

    *ppMesh = mesh;
    return true;
}

void MeshDestroy(Mesh *pMesh)
{
    glDeleteBuffers(1, &pMesh->vbo);
    glDeleteVertexArrays(1, &pMesh->vao);
    free(pMesh);
}

void MeshDraw(Mesh *pMesh)
{
    glBindVertexArray(pMesh->vao);

    glDrawArrays(GL_TRIANGLES, 0, pMesh->numVertices);

    glBindVertexArray(0);
}