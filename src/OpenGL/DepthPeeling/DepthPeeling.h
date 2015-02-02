// Shipeng Xu
// billhsu.x@gmail.com

#include <OpenGL/gl3.h>
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include "OpenGL/Shader/GLSLShader.h"

class DepthPeeling
{
public:
    DepthPeeling()
    {
        renderCallback = 0;
        colorTexture1 = 0; colorTexture2 = 0;
        depthTexture1 = 0; depthTexture2 = 0;
        compoDepth1   = 0; compoTexture1 = 0;
        framebuffer   = 0;
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 0;
        indices[4] = 2;
        indices[5] = 3;
    }
    DepthPeeling(int width, int height, int pass): windowWidth(width),
                                                   windowHeight(height),
                                                   passCount(pass),
                                                   indices{0,1,2, 0,2,3}
    {
        renderCallback = 0;
        colorTexture1 = 0; colorTexture2 = 0;
        depthTexture1 = 0; depthTexture2 = 0;
        compoDepth1   = 0; compoTexture1 = 0;
        framebuffer   = 0;
    }
    ~DepthPeeling();
    typedef void (*RenderCallback)();
    void init(RenderCallback _callback);
    void setWindowSize(int width, int height)
    {
        windowWidth = width;
        windowHeight = height;
        recreateForResolution(windowWidth, windowHeight);
    }
    void setPassCount(int pass)
    {
        passCount = pass;
    }
    void render();
    GLuint getCompoTextureId()
    {
        return compoTexture1;
    }
    GLuint colorTexture1, colorTexture2;
    GLuint depthTexture1, depthTexture2;
    GLuint compoDepth1;
    GLuint compoTexture1;
private:
    void setColorTextureSize(GLuint texture, int width, int height);
    void setDepthTextureSize(GLuint texture, int width, int height);
    GLuint createTexture();
    void recreateForResolution(int width, int height);
    void clearTextures(GLuint depthTexture, GLuint colorTexture);
    void peelingPass(GLuint depthTexture, GLuint colorTexture, GLuint peelDepthTexture);
    void compoPass(GLuint depthTexture, GLuint colorTexture, GLuint compoTexture, bool firstPass);
    
    int windowWidth, windowHeight, passCount;
    
    GLuint framebuffer;
    GLSLShader compoProgram;
    RenderCallback renderCallback;
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    float verticesArray[12];
    float uvArray[8];
    int indices[6];
};