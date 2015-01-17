// Shipeng Xu
// billhsu.x@gmail.com

#include "PlaneRenderer.h"
namespace PlaneRenderer
{
    void prepareRenderData()
    {
        indexBufferData[0] = 0;
        indexBufferData[1] = 1;
        indexBufferData[2] = 2;

        indexBufferData[3] = 0;
        indexBufferData[4] = 2;
        indexBufferData[5] = 3;
        
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
        
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);
        
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferData), indexBufferData, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glGenVertexArrays(1, &vertexArrayObj);
    }
    void render(Plane p, Vector4 color)
    {
        
    }
}