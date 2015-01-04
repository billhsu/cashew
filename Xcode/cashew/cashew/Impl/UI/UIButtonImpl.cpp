// Shipeng Xu
// billhsu.x@gmail.com

#include "UIButtonImpl.h"
#include <iostream>
UIButtonImpl::~UIButtonImpl()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &indexBuffer);
}
void UIButtonImpl::render()
{
    verticesArray[0] = vertices[0].x; verticesArray[1] = vertices[0].y;
    verticesArray[2] = vertices[1].x; verticesArray[3] = vertices[1].y;
    verticesArray[4] = vertices[2].x; verticesArray[5] = vertices[2].y;
    verticesArray[6] = vertices[3].x; verticesArray[7] = vertices[3].y;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), NULL, GL_DYNAMIC_DRAW);
    
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
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
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

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), verticesArray, GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvArray), uvArray, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorArray), colorArray, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), 0, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}