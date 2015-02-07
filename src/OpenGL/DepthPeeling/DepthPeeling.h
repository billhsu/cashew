// Shipeng Xu
// billhsu.x@gmail.com

#include <OpenGL/gl3.h>
#include <vector>
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include "OpenGL/Shader/GLSLShader.h"

class DepthPeeling
{
public:
    static DepthPeeling& getInstance()
    {
        static DepthPeeling instance;
        std::cout <<"DepthPeeling getInstance()"<<std::endl;
        return instance;
    }
    typedef void (*RenderCallback)();
    void init();
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
    
    void addToRenderCallbackList(RenderCallback callback)
    {
        renderCallbackList.push_back(callback);
    }
    
private:
    DepthPeeling()
    {
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
        windowWidth  = 0;
        windowHeight = 0;
        passCount    = 0;
    }
    ~DepthPeeling();
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
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    float verticesArray[12];
    float uvArray[8];
    int indices[6];
    
    GLuint colorTexture1, colorTexture2;
    GLuint depthTexture1, depthTexture2;
    GLuint compoDepth1;
    GLuint compoTexture1;
    
    std::vector<RenderCallback> renderCallbackList;
    void clearRenderCallbackList()
    {
        renderCallbackList.clear();
    }
    void runRenderCallbackList()
    {
        for_each(renderCallbackList.begin(), renderCallbackList.end(),
                 [](RenderCallback callbackFunc){callbackFunc();});
    }
};