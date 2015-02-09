// Shipeng Xu
// billhsu.x@gmail.com

#include "UIButtonImpl.h"

UIButtonImpl::~UIButtonImpl()
{
    std::cout<<"~UIButtonImpl("<<this<<")"<<std::endl;
}
void UIButtonImpl::render()
{
    verticesArray[0] = vertices[0].x; verticesArray[1] = vertices[0].y;
    verticesArray[2] = vertices[1].x; verticesArray[3] = vertices[1].y;
    verticesArray[4] = vertices[2].x; verticesArray[5] = vertices[2].y;
    verticesArray[6] = vertices[3].x; verticesArray[7] = vertices[3].y;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_idle);
    HardwareBuffer::VBOStruct _VBO;
    _VBO.vertexBufferData = verticesArray;
    _VBO.vertexBufferSize = sizeof(verticesArray) / sizeof(float);
    buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER);
    buffer.render();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void UIButtonImpl::prepareRenderData()
{
    uvArray[0] = 0.0f; uvArray[1] = 0.0f;
    uvArray[2] = 1.0f; uvArray[3] = 0.0f;
    uvArray[4] = 1.0f; uvArray[5] = 1.0f;
    uvArray[6] = 0.0f; uvArray[7] = 1.0f;
    
    colorArray[ 0] = mR; colorArray[ 1] = mG;  colorArray[ 2] = mB; colorArray[ 3] = mAlpha;
    colorArray[ 4] = mR; colorArray[ 5] = mG;  colorArray[ 6] = mB; colorArray[ 7] = mAlpha;
    colorArray[ 8] = mR; colorArray[ 9] = mG;  colorArray[10] = mB; colorArray[11] = mAlpha;
    colorArray[12] = mR; colorArray[13] = mG;  colorArray[14] = mB; colorArray[15] = mAlpha;
    VBOInfo.vertexBufferSize = sizeof(verticesArray) / sizeof(float);
    VBOInfo.vertexBufferData = verticesArray;
    VBOInfo.uvBufferSize = sizeof(uvArray) / sizeof(float);
    VBOInfo.uvBufferData = uvArray;
    VBOInfo.indexBufferSize = sizeof(indices) / sizeof(int);
    VBOInfo.indexBufferData = indices;
    unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER
    | HardwareBuffer::FLAG_UV_BUFFER
    | HardwareBuffer::FLAG_INDEX_BUFFER;

    buffer.initVBO(VBOInfo, flags);
    buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
    buffer.setVBOLocation(HardwareBuffer::FLAG_UV_BUFFER, 1);
    
    buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 2);
    buffer.setVBOUnitSize(HardwareBuffer::FLAG_UV_BUFFER, 2);
}