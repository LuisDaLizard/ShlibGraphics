#include <ShlibGraphics.h>
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

typedef struct TriangleVertex
{
    Vec2 position;
    Vec3 color;
} TriangleVertex;

typedef struct QuadVertex
{
    Vec2 position;
    Vec2 texture;
} QuadVertex;

TriangleVertex mTriangleData[] =
        {
                {{0, 0.5f}, {1, 0, 0}},
                {{0.5f, -0.5f}, {0, 1, 0}},
                {{-0.5f, -0.5f}, {0, 0, 1}},
        };

QuadVertex mQuadData[] =
        {
                {{-1, 1}, {0, 1}},
                {{1, 1}, {1, 1}},
                {{1, -1}, {1, 0}},

                {{1, -1}, {1, 0}},
                {{-1, -1}, {0, 0}},
                {{-1, 1}, {0, 1}},
        };

int mTriangleAttribs[] = { 2, 3 };
int mQuadAttribs[] = {2, 2};

Window gWindow;
Program gShader;
Mesh gTriMesh, gQuadMesh;
Framebuffer gFramebuffer;

void InitWindow();
void InitProgram();
void InitMesh();
void InitFramebuffer();

int main()
{
    InitWindow();
    InitProgram();
    InitMesh();
    InitFramebuffer();

    while(!WindowShouldClose(gWindow))
    {
        GLClear();

        ProgramUse(gShader);
        MeshDraw(gTriMesh);

        WindowPollEvents(gWindow);
        WindowSwapBuffers(gWindow);
    }

    return 0;
}

void InitWindow()
{
    WindowCreateInfo createInfo = { 0 };
    createInfo.glVersionMajor = 3;
    createInfo.glVersionMinor = 3;
    createInfo.width = 800;
    createInfo.height = 600;
    createInfo.pTitle = "04 - Framebuffer";

    WindowInit(&createInfo, &gWindow);
    GLClearColor(0, 0, 0, 1);
}

void InitProgram()
{
    ProgramCreateInfo program = { 0 };
    program.pVertexSource = vSource;
    program.pFragmentSource = fSource;

    if (!ProgramCreate(&program, &gShader))
        exit(1);
}

void InitMesh()
{
    MeshCreateInfo triangle = { 0 };
    triangle.stride = sizeof(TriangleVertex);
    triangle.numVertices = 3;
    triangle.pVertexData = (float *)mTriangleData;
    triangle.numAttributes = 2;
    triangle.pAttributeComponents = mTriangleAttribs;
    triangle.topology = TOPOLOGY_TRIANGLES;

    if (!MeshCreate(&triangle, &gTriMesh))
        exit(2);

    MeshCreateInfo quad = { 0 };
    quad.stride = sizeof(QuadVertex);
    quad.numVertices = 6;
    quad.pVertexData = (float *)mQuadData;
    quad.numAttributes = 2;
    quad.pAttributeComponents = mQuadAttribs;
    quad.topology = TOPOLOGY_TRIANGLES;

    if (!MeshCreate(&quad, &gQuadMesh))
        exit(2);
}

void InitFramebuffer()
{
    FramebufferCreateInfo createInfo = { 0 };
    createInfo.width = 800;
    createInfo.height = 600;
    createInfo.useRenderbuffer = true;
    createInfo.attachmentCount = 1;

    if (!FramebufferCreate(&createInfo, &gFramebuffer))
        exit(3);
}