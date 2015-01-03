// Shipeng Xu
// billhsu.x@gmail.com

#include "UIButtonImpl.h"
#include <iostream>
void UIButtonImpl::render()
{
    
}

void UIButtonImpl::prepareRenderData()
{
    verticesArray[0] = vertices[0].x; verticesArray[1] = vertices[0].y;
    verticesArray[2] = vertices[1].x; verticesArray[3] = vertices[1].y;
    verticesArray[4] = vertices[2].x; verticesArray[5] = vertices[2].y;
    verticesArray[6] = vertices[3].x; verticesArray[7] = vertices[3].y;

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), NULL, GL_STREAM_DRAW);
    
    float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if(ptr != NULL)
    {
        memcpy(ptr, verticesArray, sizeof(verticesArray));
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    else
    {
        std::cout<<"UIButtonImpl::prepareRenderData() - glMapBuffer failed"<<std::endl;
    }

}