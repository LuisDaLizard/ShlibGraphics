#include "Texture.h"

#include <stdlib.h>
#include <glad/glad.h>

bool Texture2DCreate(Texture2DCreateInfo *pCreateInfo, Texture *pTexture)
{
    Texture texture = malloc(sizeof(struct sTexture));
    texture->textureType = GL_TEXTURE_2D;

    glGenTextures(1, &texture->textureID);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pCreateInfo->params.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pCreateInfo->params.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pCreateInfo->params.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pCreateInfo->params.magFilter);

    switch(pCreateInfo->channels)
    {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pData);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pData);
            break;
        default:
            return false;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    *pTexture = texture;
    return true;
}

bool TextureCubeCreate(TextureCubeCreateInfo *pCreateInfo, Texture *pTexture)
{
    Texture texture = malloc(sizeof(struct sTexture));
    texture->textureType = GL_TEXTURE_CUBE_MAP;

    glGenTextures(1, &texture->textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pCreateInfo->params.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pCreateInfo->params.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pCreateInfo->params.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pCreateInfo->params.magFilter);

    switch(pCreateInfo->channels)
    {
        case 3:
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pDataPX);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pDataNX);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pDataPY);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pDataNY);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pDataPZ);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, pCreateInfo->width, pCreateInfo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pCreateInfo->pDataNZ);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pDataPX);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pDataNX);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pDataPY);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pDataNY);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pDataPZ);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, pCreateInfo->width, pCreateInfo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pCreateInfo->pDataNZ);
            break;
        default:
            return false;
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return true;
}

bool TextureDepthCreate(TextureDepthCreateInfo *pCreateInfo, Texture *pTexture)
{
    Texture texture = malloc(sizeof(struct sTexture));
    texture->textureType = GL_TEXTURE_2D;

    glGenTextures(1, &texture->textureID);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pCreateInfo->params.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pCreateInfo->params.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pCreateInfo->params.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pCreateInfo->params.magFilter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, pCreateInfo->width, pCreateInfo->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pCreateInfo->pData);

    glBindTexture(GL_TEXTURE_2D, 0);

    *pTexture = texture;
    return true;
}

void TextureDestroy(Texture texture)
{
    glDeleteTextures(1, &texture->textureID);
    free(texture);
}

void TextureBind(Texture texture, int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(texture->textureType, texture->textureID);
}