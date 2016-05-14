// Shipeng Xu
// billhsu.x@gmail.com

#pragma once

#include <OpenGL/gl3.h>
#include <iostream>
#include <map>

class HardwareBuffer {
   public:
    HardwareBuffer() {
        flags = 0;
        vertexBuffer = -1;
        extraBuffer1 = -1;
        extraBuffer2 = -1;
        extraBuffer3 = -1;
        extraBuffer4 = -1;
        extraBuffer5 = -1;
        uvBuffer = -1;
        colorBuffer = -1;
        indexBuffer = -1;
        vertexArrayObj = -1;
        for (int i = 0; i < sizeof(VBOLocation) / sizeof(int); ++i) {
            VBOLocation[i] = -1;
        }
        for (int i = 0; i < sizeof(VBOUnitSize) / sizeof(int); ++i) {
            VBOUnitSize[i] = 0;
        }
        std::cout << "HardwareBuffer()" << std::endl;
    };
    ~HardwareBuffer() {
        if (vertexBuffer != -1)
            glDeleteBuffers(1, &vertexBuffer);
        if (extraBuffer1 != -1)
            glDeleteBuffers(1, &extraBuffer1);
        if (extraBuffer2 != -1)
            glDeleteBuffers(1, &extraBuffer2);
        if (extraBuffer3 != -1)
            glDeleteBuffers(1, &extraBuffer3);
        if (extraBuffer4 != -1)
            glDeleteBuffers(1, &extraBuffer4);
        if (extraBuffer5 != -1)
            glDeleteBuffers(1, &extraBuffer5);
        if (uvBuffer != -1)
            glDeleteBuffers(1, &uvBuffer);
        if (colorBuffer != -1)
            glDeleteBuffers(1, &colorBuffer);
        if (indexBuffer != -1)
            glDeleteBuffers(1, &indexBuffer);
        if (vertexArrayObj != -1)
            glDeleteVertexArrays(1, &vertexArrayObj);
        std::cout << "~HardwareBuffer()" << std::endl;
    }

    static const unsigned int FLAG_VERTEX_BUFFER = 0x0001;
    static const unsigned int FLAG_UV_BUFFER = 0x0002;
    static const unsigned int FLAG_COLOR_BUFFER = 0x0004;
    static const unsigned int FLAG_INDEX_BUFFER = 0x0008;
    // extra buffer 1..5 are for storing extra info
    // normal, tangent, etc.
    static const unsigned int FLAG_EXTRA_BUFFER_1 = 0x0010;
    static const unsigned int FLAG_EXTRA_BUFFER_2 = 0x0020;
    static const unsigned int FLAG_EXTRA_BUFFER_3 = 0x0040;
    static const unsigned int FLAG_EXTRA_BUFFER_4 = 0x0080;
    static const unsigned int FLAG_EXTRA_BUFFER_5 = 0x0100;

    struct VBOStruct {
        VBOStruct() {
            vertexBufferSize = 0;
            vertexBufferData = 0;
            extraBuffer1Size = 0;
            extraBuffer1Data = 0;
            extraBuffer2Size = 0;
            extraBuffer2Data = 0;
            extraBuffer3Size = 0;
            extraBuffer3Data = 0;
            extraBuffer4Size = 0;
            extraBuffer4Data = 0;
            extraBuffer5Size = 0;
            extraBuffer5Data = 0;
            uvBufferSize = 0;
            uvBufferData = 0;
            colorBufferSize = 0;
            colorBufferData = 0;
            indexBufferSize = 0;
            indexBufferData = 0;
        }
        float* vertexBufferData;
        int vertexBufferSize;
        float* extraBuffer1Data;
        int extraBuffer1Size;
        float* extraBuffer2Data;
        int extraBuffer2Size;
        float* extraBuffer3Data;
        int extraBuffer3Size;
        float* extraBuffer4Data;
        int extraBuffer4Size;
        float* extraBuffer5Data;
        int extraBuffer5Size;
        float* uvBufferData;
        int uvBufferSize;
        float* colorBufferData;
        int colorBufferSize;
        int* indexBufferData;
        int indexBufferSize;
    };

    void initVBO(const VBOStruct vboStruct, unsigned int vboFlag);
    void updateVBO(const VBOStruct vboStruct, unsigned int vboFlag);
    void render(GLenum mode = GL_TRIANGLES, int unitSize = 3);

    int VBOLocation[512];
    int VBOUnitSize[512];

    std::map<int, int> bufferIdToBufferSize;

    void setVBOLocation(unsigned int vboFlag, int location);
    void setVBOUnitSize(unsigned int vboFlag, int unitSize);

   private:
    template <typename T>
    void bufferGenBind(GLuint& bufferID, int bufferSize, T* bufferData,
                       GLenum bufferType, GLenum bufferUsage);
    template <typename T>
    void bufferUpdate(GLuint& bufferID, int bufferSize, T* bufferData,
                      GLenum bufferType, GLenum bufferUsage);
    unsigned int flags;
    VBOStruct VBOInfo;
    GLuint vertexBuffer;
    GLuint extraBuffer1;
    GLuint extraBuffer2;
    GLuint extraBuffer3;
    GLuint extraBuffer4;
    GLuint extraBuffer5;
    GLuint uvBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint vertexArrayObj;
};