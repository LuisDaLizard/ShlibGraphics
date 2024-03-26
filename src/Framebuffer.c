#include "ShlibGraphics/Framebuffer.h"
#include "ShlibGraphics/Utils.h"

#include <stdlib.h>
#include <glad/glad.h>

bool FramebufferCreate(FramebufferCreateInfo *pCreateInfo, Framebuffer *pFramebuffer)
{
    Framebuffer framebuffer = malloc(sizeof(struct sFramebuffer));
    framebuffer->width = pCreateInfo->width;
    framebuffer->height = pCreateInfo->height;
    framebuffer->attachmentCount = pCreateInfo->attachmentCount;
    framebuffer->pAttachments = malloc(pCreateInfo->attachmentCount * sizeof(Texture));

    glGenFramebuffers(1, &framebuffer->framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->framebufferID);

    if (pCreateInfo->useRenderbuffer)
    {
        glGenRenderbuffers(1, &framebuffer->renderbufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->renderbufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pCreateInfo->width, pCreateInfo->height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, framebuffer->renderbufferID);
    }

    int i;
    for (i = 0; i < pCreateInfo->attachmentCount; i++)
    {
        Texture texture;

        TextureParams params = { 0 };
        params.wrapS = WRAP_CLAMP_TO_EDGE;
        params.wrapT = WRAP_CLAMP_TO_EDGE;
        params.minFilter = MIN_NEAREST;
        params.magFilter = MAG_NEAREST;

        Texture2DCreateInfo createInfo = { 0 };
        createInfo.width = framebuffer->width;
        createInfo.height = framebuffer->height;
        createInfo.channels = 3;
        createInfo.pData = NULL;
        createInfo.params = params;

        if (!Texture2DCreate(&createInfo, &texture))
            return false;

        framebuffer->pAttachments[i] = texture;

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture->textureID, 0);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        CheckGLErrors();
        free(framebuffer);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    *pFramebuffer = framebuffer;
    return true;
}

void FramebufferDestroy(Framebuffer framebuffer)
{
    if (framebuffer->renderbufferID)
        glDeleteRenderbuffers(1, &framebuffer->renderbufferID);

    glDeleteFramebuffers(1, &framebuffer->framebufferID);

    free(framebuffer);
}

void FramebufferBegin(Framebuffer framebuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->framebufferID);
    glViewport(0, 0, framebuffer->width, framebuffer->height);
}

void FramebufferEnd(Framebuffer framebuffer, int width, int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}

Texture FramebufferGetAttachment(Framebuffer framebuffer, int index)
{
    if (index < 0 || index >= framebuffer->attachmentCount)
        return NULL;
    return framebuffer->pAttachments[index];
}
