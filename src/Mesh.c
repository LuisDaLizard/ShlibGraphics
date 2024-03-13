#include "Mesh.h"

#include <glad/glad.h>
#include <stdlib.h>

bool MeshCreate(MeshCreateInfo *pCreateInfo, Mesh *pMesh)
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

    Mesh mesh = malloc(sizeof(struct sMesh));
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

    *pMesh = mesh;
    return true;
}

void MeshDestroy(Mesh mesh)
{
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    free(mesh);
}

void MeshDraw(Mesh mesh)
{
    glBindVertexArray(mesh->vao);

    glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);

    glBindVertexArray(0);
}