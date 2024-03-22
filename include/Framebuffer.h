#ifndef SHLIB_FRAMEBUFFER_H
#define SHLIB_FRAMEBUFFER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "Texture.h"

typedef struct sColorAttachmentCreateInfo {
    bool useDrawBuffer;
} ColorAttachmentCreateInfo;

struct sFramebufferCreateInfo {
    int width;
    int height;

    bool useRenderbuffer;

    int attachmentCount;
    ColorAttachmentCreateInfo *pAttachments; // TODO: no purpose yet.
};

struct sFramebuffer {
    int width;
    int height;

    unsigned int framebufferID;
    unsigned int renderbufferID;

    int attachmentCount;
    Texture *pAttachments;
};

typedef struct sFramebufferCreateInfo FramebufferCreateInfo;
typedef struct sFramebuffer *Framebuffer;

bool FramebufferCreate(FramebufferCreateInfo *pCreateInfo, Framebuffer *pFramebuffer);

void FramebufferDestroy(Framebuffer framebuffer);

void FramebufferBegin(Framebuffer framebuffer);

void FramebufferEnd(Framebuffer framebuffer, int width, int height);

Texture FramebufferGetAttachment(Framebuffer framebuffer, int index);

#ifdef __cplusplus
}
#endif

#endif //SHLIB_FRAMEBUFFER_H
