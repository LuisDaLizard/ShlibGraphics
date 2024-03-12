#include <Shlib.h>
#include <stdio.h>
#include <stdlib.h>

const char *vSource = "#version 330 core\n"
                      "layout (location = 0) in vec2 aPosition;\n"
                      "layout (location = 1) in vec3 aColor;\n"
                      "out vec3 fColor;\n"
                      "void main()\n"
                      "{\n"
                      "\tfColor = aColor;\n"
                      "\tgl_Position = vec4(aPosition, 0, 1);\n"
                      "}\n";
const char *fSource = "#version 330 core\n"
                      "out vec4 oColor;\n"
                      "in vec3 fColor;\n"
                      "void main()\n"
                      "{\n"
                      "\toColor = vec4(fColor, 1);\n"
                      "}\n";

float mData[] = { 0, 0.5f, 1, 0, 0,
                  0.5f, -0.5f, 0, 1, 0,
                  -0.5f, -0.5f, 0, 0, 1};
int mAttribs[] = { 2, 3 };

Program *gShader;
Mesh *gMesh;

void Init();
void Draw();

int main()
{
    Application *pApp = NULL;

    AppCreateInfo createInfo = { 0 };
    createInfo.width = 800;
    createInfo.height = 600;
    createInfo.pTitle = "02 - Mesh";
    createInfo.pInitFunction = Init;
    createInfo.pDrawFunction = Draw;

    ApplicationInit(&createInfo, &pApp);

    ApplicationRun(pApp);

    ApplicationFree(pApp);

    return 0;
}

void Init()
{
    ProgramCreateInfo program = { 0 };
    program.pVertexSource = vSource;
    program.pFragmentSource = fSource;

    if (!ProgramCreate(&program, &gShader))
        exit(1);

    MeshCreateInfo mesh = { 0 };
    mesh.stride = sizeof(Vec2) + sizeof(Vec3);
    mesh.numVertices = 3;
    mesh.pVertexData = mData;
    mesh.numAttributes = 2;
    mesh.pAttributeComponents = mAttribs;

    if (!MeshCreate(&mesh, &gMesh))
        exit(1);
}

void Draw()
{
    ProgramUse(gShader);
    MeshDraw(gMesh);
}