#ifndef SHLIB_TEXTURE_H
#define SHLIB_TEXTURE_H

#include <stdbool.h>

typedef enum eTextureWrap
{
    WRAP_CLAMP_TO_EDGE = 0x812f,
    WRAP_CLAMP_TO_BORDER = 0x812d,
    WRAP_MIRRORED_REPEAT = 0x8370,
    WRAP_REPEAT = 0x2901,
} TextureWrap;

typedef enum eTextureMin
{
    MIN_NEAREST = 0x2600,
    MIN_LINEAR = 0x2601,
    MIN_NEAREST_MIPMAP_NEAREST = 0x2700,
    MIN_LINEAR_MIPMAP_NEAREST = 0x2701,
    MIN_NEAREST_MIPMAP_LINEAR = 0x2702,
    MIN_LINEAR_MIPMAP_LINEAR = 0x2703,
} TextureMin;

typedef enum eTextureMag
{
    MAG_NEAREST = 0x2600,
    MAG_LINEAR = 0x2601,
} TextureMag;

typedef struct sTextureParams
{
    TextureWrap wrapS;
    TextureWrap wrapT;
    TextureMin minFilter;
    TextureMag magFilter;
} TextureParams;

struct sTexture2DCreateInfo
{
    int width;
    int height;
    int channels;

    void *pData;

    TextureParams params;
};

struct sTextureCubeCreateInfo
{
    int width;
    int height;
    int channels;

    void *pDataPX;
    void *pDataNX;
    void *pDataPY;
    void *pDataNY;
    void *pDataPZ;
    void *pDataNZ;

    TextureParams params;
};

struct sTextureDepthCreateInfo
{
    int width;
    int height;

    void *pData;

    TextureParams params;
};

struct sTexture
{
    unsigned int textureID;
    unsigned int textureType;
};

typedef struct sTexture2DCreateInfo Texture2DCreateInfo;
typedef struct sTextureCubeCreateInfo TextureCubeCreateInfo;
typedef struct sTextureDepthCreateInfo TextureDepthCreateInfo;
typedef struct sTexture *Texture;

bool Texture2DCreate(Texture2DCreateInfo *pCreateInfo, Texture *pTexture);
bool TextureCubeCreate(TextureCubeCreateInfo *pCreateInfo, Texture *pTexture);
bool TextureDepthCreate(TextureDepthCreateInfo *pCreateInfo, Texture *pTexture);
void TextureDestroy(Texture texture);
void TextureBind(Texture texture, int slot);

#endif //SHLIB_TEXTURE_H
