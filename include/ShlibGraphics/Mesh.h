#ifndef SHLIB_MESH_H
#define SHLIB_MESH_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef enum eMeshTopology
{
    TOPOLOGY_POINTS = 0x0000,
    TOPOLOGY_TRIANGLES = 0x0004,
    TOPOLOGY_PATCHES = 0x000E,
} MeshTopology;

struct sMeshCreateInfo {
    int stride;
    int numVertices;
    float *pVertexData;
    int numAttributes;
    int *pAttributeComponents;
    MeshTopology topology;
};

struct sMesh {
    unsigned int vao;
    unsigned int vbo;
    int numVertices;
    MeshTopology topology;
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
