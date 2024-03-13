#include <ShlibGraphics.h>
#include <stdlib.h>

const char *vSource = "#version 330 core\n"
                      "layout (location = 0) in vec2 aPosition;\n"
                      "layout (location = 1) in vec2 aTexCoords;\n"
                      "out vec2 fTexCoords;\n"
                      "void main()\n"
                      "{\n"
                      "\tfTexCoords = aTexCoords;\n"
                      "\tgl_Position = vec4(aPosition, 0, 1);\n"
                      "}\n";
const char *fSource = "#version 330 core\n"
                      "out vec4 oColor;\n"
                      "uniform sampler2D uTexture0;\n"
                      "in vec2 fTexCoords;\n"
                      "void main()\n"
                      "{\n"
                      "\toColor = texture(uTexture0, fTexCoords);\n"
                      "}\n";

float mData[] = { 0, 0.5f,      0.5f, 1,
                  0.5f, -0.5f,  1, 0,
                  -0.5f, -0.5f, 0, 0};
int mAttribs[] = { 2, 2 };
unsigned char mTextureData[] = {255, 0, 0, 255,
                                0, 255, 0, 255,
                                0, 0, 255, 255,
                                0, 0, 0, 255};

Window gWindow;
Program gShader;
Mesh gMesh;
Texture gTexture;

void InitWindow();
void InitProgram();
void InitMesh();
void InitTexture();

int main()
{
    InitWindow();
    InitProgram();
    InitMesh();
    InitTexture();

    while(!WindowShouldClose(gWindow))
    {
        WindowClear();

        ProgramUse(gShader);
        TextureBind(gTexture, 0);
        MeshDraw(gMesh);

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
    createInfo.pTitle = "03 - Texture";

    WindowInit(&createInfo, &gWindow);
    WindowSetClearColor(1, 1, 1);
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
    MeshCreateInfo mesh = { 0 };
    mesh.stride = sizeof(Vec2) + sizeof(Vec2);
    mesh.numVertices = 3;
    mesh.pVertexData = mData;
    mesh.numAttributes = 2;
    mesh.pAttributeComponents = mAttribs;

    if (!MeshCreate(&mesh, &gMesh))
        exit(2);
}

void InitTexture()
{
    TextureParams params = { 0 };
    params.wrapT = WRAP_CLAMP_TO_EDGE;
    params.wrapS = WRAP_CLAMP_TO_EDGE;
    params.minFilter = MIN_LINEAR;
    params.magFilter = MAG_LINEAR;

    Texture2DCreateInfo texture = { 0 };
    texture.width = 2;
    texture.height = 2;
    texture.channels = 4;
    texture.pData = mTextureData;
    texture.params = params;

    if (!Texture2DCreate(&texture, &gTexture))
        exit(3);
}