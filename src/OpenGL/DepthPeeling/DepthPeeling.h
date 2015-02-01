// Shipeng Xu
// billhsu.x@gmail.com

#include <OpenGL/gl3.h>

class DepthPeeling
{
public:
    DepthPeeling(){}
    DepthPeeling(int width, int height, int pass): windowWidth(width), windowHeight(height), passCount(pass){}
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
private:
    void setColorTextureSize(GLuint texture, int width, int height);
    void setDepthTextureSize(GLuint texture, int width, int height);
    GLuint createTexture();
    void recreateForResolution(int width, int height);
    void clearTextures(GLuint depthTexture, GLuint colorTexture);
    void peelingPass(GLuint depthTexture, GLuint colorTexture, GLuint peelDepthTexture);
    
    int windowWidth, windowHeight, passCount;
    GLuint colorTexture1, colorTexture2;
    GLuint depthTexture1, depthTexture2;
    GLuint compoDepth1;
    GLuint compoTexture1;
    GLuint framebuffer;
    RenderCallback mRenderCallback;
};