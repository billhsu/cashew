// Shipeng Xu
// billhsu.x@gmail.com
// Thanks to https://github.com/Kopakc/Visu

#include "DepthPeeling.h"
#include <stdio.h>

DepthPeeling::~DepthPeeling()
{
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &colorTexture1);
    glDeleteTextures(1, &colorTexture2);
    glDeleteTextures(1, &depthTexture1);
    glDeleteTextures(1, &depthTexture2);
    glDeleteTextures(1, &compoTexture1);
    glDeleteTextures(1, &compoDepth1);
}
void DepthPeeling::init(RenderCallback _callback)
{
    glGenFramebuffers(1, &framebuffer);
    colorTexture1 = createTexture();
    colorTexture2 = createTexture();
    depthTexture1 = createTexture();
    depthTexture2 = createTexture();
    compoTexture1 = createTexture();
    compoDepth1 = createTexture();
    recreateForResolution(windowWidth, windowHeight);
}
void DepthPeeling::setColorTextureSize(GLuint texture, int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

void DepthPeeling::setDepthTextureSize(GLuint texture, int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
}
GLuint DepthPeeling::createTexture()
{
    GLuint texture;
    glGenTextures(1, &texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    return texture;
}

void DepthPeeling::recreateForResolution(int width, int height)
{
    printf("recreateForResolution %d, %d\n", width, height);
    setColorTextureSize(colorTexture1, width, height);
    setColorTextureSize(colorTexture2, width, height);
    setDepthTextureSize(depthTexture1, width, height);
    setDepthTextureSize(depthTexture2, width, height);
    setColorTextureSize(compoTexture1, width, height);
    setDepthTextureSize(compoDepth1, width, height);
}

void DepthPeeling::clearTextures(GLuint depthTexture, GLuint colorTexture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void DepthPeeling::peelingPass(GLuint depthTexture, GLuint colorTexture, GLuint peelDepthTexture)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, peelDepthTexture);    
}