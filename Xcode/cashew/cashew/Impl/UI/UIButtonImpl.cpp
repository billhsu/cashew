// Shipeng Xu
// billhsu.x@gmail.com

#include "UIButtonImpl.h"
#include <iostream>


void _checkGlErr(int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err <<" "<<__FILE__<< " "<<line<<std::endl;
    }
}

typedef struct kmVec3 {
    float x;
    float y;
    float z;
} kmVec3;

typedef struct kmVec2 {
    float x;
    float y;
} kmVec2;

static const kmVec3 vertexBufferData[] = {
    {-1.0f,-1.0f,-1.0f},
    {-1.0f,-1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f,-1.0f}
};

static const kmVec3 colorBufferData[] = {
    {0.583f,  0.771f,  0.014f},
    {0.609f,  0.115f,  0.436f},
    {0.327f,  0.483f,  0.844f},
    {0.822f,  0.569f,  0.201f}
};

static const kmVec2 uvBufferData[] = {
    {0.000059f, 0.000004f},
    {0.000103f, 0.336048f},
    {0.335973f, 0.335903f},
    {1.000023f, 0.000013f}
};

UIButtonImpl::~UIButtonImpl()
{
    glDeleteBuffers(1, &vertexBuffer);
//    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObj);
}
void UIButtonImpl::render()
{
//    verticesArray[0] = vertices[0].x; verticesArray[1] = vertices[0].y;
//    verticesArray[2] = vertices[1].x; verticesArray[3] = vertices[1].y;
//    verticesArray[4] = vertices[2].x; verticesArray[5] = vertices[2].y;
//    verticesArray[6] = vertices[3].x; verticesArray[7] = vertices[3].y;
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), NULL, GL_DYNAMIC_DRAW);
//    
//    float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//    if(ptr != NULL)
//    {
//        memcpy(ptr, verticesArray, sizeof(verticesArray));
//        glUnmapBuffer(GL_ARRAY_BUFFER);
//    }
//    else
//    {
//        std::cout<<"UIButtonImpl::prepareRenderData() - glMapBuffer failed"<<std::endl;
//    }
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    
//        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    //        glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(vertexArrayObj);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), NULL, GL_DYNAMIC_DRAW);
    
    float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    static float accu=0.0f;
    accu+=0.01f;
    if(ptr != NULL)
    {
        ptr[0] = -1.0f; ptr[1] = -1.0f; ptr[2] = -1.0f;
        ptr[3] = -1.0f; ptr[4] = -1.0f; ptr[5] =  1.0f;
        ptr[6] = -1.0f; ptr[7] =  1.0f; ptr[8] =  1.0f;
        ptr[9] =  1.0f; ptr[10] =  1.0f; ptr[11] =  -1.0f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    else
    {
        std::cout<<"UIButtonImpl::prepareRenderData() - glMapBuffer failed"<<std::endl;
    }
    _checkGlErr(__LINE__);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    _checkGlErr(__LINE__);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    _checkGlErr(__LINE__);
    glActiveTexture(GL_TEXTURE0);
    _checkGlErr(__LINE__);
//    glEnable(GL_TEXTURE_2D);
    _checkGlErr(__LINE__);
    glBindTexture(GL_TEXTURE_2D, textureID_idle);
    _checkGlErr(__LINE__);
//    glDrawArrays(GL_TRIANGLES, 0, 3*3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    _checkGlErr(__LINE__);
//    glDisable(GL_TEXTURE_2D);
    _checkGlErr(__LINE__);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vertexArrayObj);
}