#ifndef SHLIB_MESH_H
#define SHLIB_MESH_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

struct sMeshCreateInfo {
    bool isStatic;
    int stride;
    int numVertices;
    float *pVertexData;
    int numAttributes;
    int *pAttributeComponents;
};

struct sMesh {
    unsigned int vao;
    unsigned int vbo;
    int numVertices;
};

typedef struct sMeshCreateInfo MeshCreateInfo;
typedef struct sMesh *Mesh;

bool MeshCreate(MeshCreateInfo *pCreateInfo, Mesh *pMesh);

void MeshDestroy(Mesh mesh);

void MeshDraw(Mesh mesh);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_MESH_H
