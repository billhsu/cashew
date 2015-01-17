// Shipeng Xu
// billhsu.x@gmail.com

#pragma once

#include <OpenGL/gl3.h>

class HardwareBuffer
{
public:
    HardwareBuffer()
    {
        flags = 0;
    };
    ~HardwareBuffer()
    {
        
    }

    static const unsigned int FLAG_VERTEX_BUFFER = 0x0001;
    static const unsigned int FLAG_UV_BUFFER     = 0x0002;
    static const unsigned int FLAG_COLOR_BUFFER  = 0x0004;
    static const unsigned int FLAG_INDEX_BUFFER  = 0x0008;
    
    struct VBOStruct
    {
        float* vertexBufferData; int vertexBufferSize;
        float* uvBufferData;     int uvBufferSize;
        float* colorBufferData;  int colorBufferSize;
        int* indexBufferData;    int indexBufferSize;
    };
    
    void initVBO(const VBOStruct vboStruct, unsigned int vboFlag);
    void updateVBO(const VBOStruct vboStruct, unsigned int vboFlag);
    void render();
    
    int VBOLocation[256];
    int VBOUnitSize[256];
    
    void setVBOLocation(unsigned int vboFlag, int location);
    void setVBOUnitSize(unsigned int vboFlag, int unitSize);
private:
    template<typename T>
    void bufferGenBind(GLuint& bufferID, int bufferSize, T* bufferData, GLenum bufferType, GLenum bufferUsage);
    unsigned int flags;
    VBOStruct VBOInfo;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint vertexArrayObj;
};