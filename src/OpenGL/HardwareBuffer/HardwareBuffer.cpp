// Shipeng Xu
// billhsu.x@gmail.com

#include "HardwareBuffer.h"
#include <iostream>

void HardwareBuffer::initVBO(VBOStruct vboStruct)
{
    if(vboStruct.vertexBufferSize != 0)
    {
        flags |= FLAG_VERTEX_BUFFER;
        bufferGenBind<float>(vertexBuffer, vboStruct.vertexBufferSize, vboStruct.vertexBufferData,
                             GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    if(vboStruct.uvBufferSize != 0)
    {
        flags |= FLAG_UV_BUFFER;
        bufferGenBind<float>(uvBuffer, vboStruct.uvBufferSize, vboStruct.uvBufferData,
                             GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    if(vboStruct.colorBufferSize != 0)
    {
        flags |= FLAG_COLOR_BUFFER;
        bufferGenBind<float>(colorBuffer, vboStruct.colorBufferSize, vboStruct.colorBufferData,
                             GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    if(vboStruct.indexBufferSize != 0)
    {
        flags |= FLAG_INDEX_BUFFER;
        bufferGenBind<int>(indexBuffer, vboStruct.indexBufferSize, vboStruct.indexBufferData,
                           GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template<typename T>
void HardwareBuffer::bufferGenBind(GLuint& bufferID, int bufferSize, T* bufferData,
                                   GLenum bufferType, GLenum bufferUsage)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(bufferType, bufferID);
    glBufferData(bufferType, bufferSize * sizeof(T), 0, bufferUsage);
    T* dataBufVertices = (T*)glMapBuffer(bufferType, GL_WRITE_ONLY);
    if(dataBufVertices == 0)
    {
        std::cerr<<"glMapBuffer failed: "<<__FILE__<<"["<<__LINE__<<"]"<<std::endl;
    }
    else
    {
        for(int i=0; i<bufferSize; i++)
        {
            dataBufVertices[i] = bufferData[i];
        }
        glUnmapBuffer(bufferType);
    }
}