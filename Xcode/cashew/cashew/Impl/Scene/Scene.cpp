#include "Scene.h"
#import <OpenGL/gl3.h>
#include "Core/Math/Vectors.h"
namespace cashew{
    GLuint sceneVertexBuffer;
    GLuint sceneColorBuffer;
    GLuint sceneVertexArrayObj;
    void drawGrid(float size, float step)
    {
    }
    static float axisCoords[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    static float axisEndCoords[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    static float axisColors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };
    void prepareScene()
    {
        // create vertex attribute buffers
        glGenBuffers(1, &sceneVertexBuffer);
        
        glGenBuffers(1, &sceneColorBuffer);
        
        // create vertex array for shader attributes
        glGenVertexArrays(1, &sceneVertexArrayObj);
    }
    void clearScene()
    {
        glDeleteBuffers(1, &sceneVertexBuffer);
        glDeleteBuffers(1, &sceneColorBuffer);
        glDeleteVertexArrays(1, &sceneVertexArrayObj);
    }
    void drawAxis(float size)
    {
        axisCoords[3] = size;
        axisCoords[10] = size;
        axisCoords[17] = size;
        
        axisEndCoords[0] = size;
        axisEndCoords[4] = size;
        axisEndCoords[8] = size;
        
        // create vertex attribute buffers
        glBindBuffer(GL_ARRAY_BUFFER, sceneVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axisCoords), axisCoords, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axisColors), axisColors, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // create vertex array for shader attributes
        glBindVertexArray(sceneVertexArrayObj);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneVertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, sceneColorBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        
        glDrawArrays(GL_LINES, 0, 6*3);
        
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        
    }
}