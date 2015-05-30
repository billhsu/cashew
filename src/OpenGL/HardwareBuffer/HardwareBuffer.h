// Shipeng Xu
// billhsu.x@gmail.com

#pragma once

#include <OpenGL/gl3.h>
#include <iostream>

class HardwareBuffer
{
public:
    HardwareBuffer()
    {
        flags = 0;
        vertexBuffer = -1;
        uvBuffer = -1;
        colorBuffer = -1;
        indexBuffer = -1;
        vertexArrayObj = -1;
        for(int i=0; i<sizeof(VBOLocation)/sizeof(int); ++i)
        {
            VBOLocation[i] = -1;
        }
        for(int i=0; i<sizeof(VBOUnitSize)/sizeof(int); ++i)
        {
            VBOUnitSize[i] = 0;
        }
        std::cout<<"HardwareBuffer()"<<std::endl;
    };
    ~HardwareBuffer()
    {
        if(vertexBuffer != -1)   glDeleteBuffers(1, &vertexBuffer);
        if(uvBuffer != -1)       glDeleteBuffers(1, &uvBuffer);
        if(colorBuffer != -1)    glDeleteBuffers(1, &colorBuffer);
        if(indexBuffer != -1)    glDeleteBuffers(1, &indexBuffer);
        if(vertexArrayObj != -1) glDeleteVertexArrays(1, &vertexArrayObj);
        std::cout<<"~HardwareBuffer()"<<std::endl;
    }
    
    static const unsigned int FLAG_VERTEX_BUFFER = 0x0001;
    static const unsigned int FLAG_UV_BUFFER     = 0x0002;
    static const unsigned int FLAG_COLOR_BUFFER  = 0x0004;
    static const unsigned int FLAG_INDEX_BUFFER  = 0x0008;
    
    struct VBOStruct
    {
        VBOStruct()
        {
            vertexBufferSize = 0;
            vertexBufferData = 0;
            uvBufferSize = 0;
            uvBufferData = 0;
            colorBufferSize = 0;
            colorBufferData = 0;
            indexBufferSize = 0;
            indexBufferData = 0;
        }
        float* vertexBufferData; int vertexBufferSize;
        float* uvBufferData;     int uvBufferSize;
        float* colorBufferData;  int colorBufferSize;
        int* indexBufferData;    int indexBufferSize;
    };
    
    void initVBO(const VBOStruct vboStruct, unsigned int vboFlag);
    void updateVBO(const VBOStruct vboStruct, unsigned int vboFlag);
    void render(GLenum mode = GL_TRIANGLES, int unitSize = 3);
    
    int VBOLocation[256];
    int VBOUnitSize[256];
    
    void setVBOLocation(unsigned int vboFlag, int location);
    void setVBOUnitSize(unsigned int vboFlag, int unitSize);
private:
    template<typename T>
    void bufferGenBind(GLuint& bufferID, int bufferSize, T* bufferData, GLenum bufferType, GLenum bufferUsage);
    template<typename T>
    void bufferUpdate(GLuint& bufferID, int bufferSize, T* bufferData, GLenum bufferType, GLenum bufferUsage);
    unsigned int flags;
    VBOStruct VBOInfo;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint vertexArrayObj;
};