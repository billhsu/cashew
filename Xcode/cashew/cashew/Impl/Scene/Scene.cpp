// Shipeng Xu
// billhsu.x@gmail.com

#include "Scene.h"
#import <OpenGL/gl3.h>
#include "Core/Math/Vectors.h"
namespace cashew{
    GLuint sceneAxisVertexBuffer;
    GLuint sceneAxisEndVertexBuffer;
    GLuint sceneAxisColorBuffer;
    GLuint sceneAxisEndColorBuffer;
    GLuint sceneAxisVertexArrayObj;
    GLuint sceneAxisEndVertexArrayObj;
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
    static float axisEndColors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    void prepareSceneAxis(float size)
    {
        axisCoords[3] = size;
        axisCoords[10] = size;
        axisCoords[17] = size;
        
        axisEndCoords[0] = size;
        axisEndCoords[4] = size;
        axisEndCoords[8] = size;
        // create vertex attribute buffers
        glGenBuffers(1, &sceneAxisVertexBuffer);
        glGenBuffers(1, &sceneAxisEndVertexBuffer);
        glGenBuffers(1, &sceneAxisColorBuffer);
        glGenBuffers(1, &sceneAxisEndColorBuffer);
        // create vertex array for shader attributes
        glGenVertexArrays(1, &sceneAxisVertexArrayObj);
        glGenVertexArrays(1, &sceneAxisEndVertexArrayObj);
        
        // create vertex attribute buffers
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axisCoords), axisCoords, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisEndVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axisEndCoords), axisEndCoords, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axisColors), axisColors, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisEndColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axisEndColors), axisEndColors, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // create vertex array for shader attributes
        glBindVertexArray(sceneAxisVertexArrayObj);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisVertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisColorBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(sceneAxisEndVertexArrayObj);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisEndVertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, sceneAxisEndColorBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    }
    void clearScene()
    {
        glDeleteBuffers(1, &sceneAxisVertexBuffer);
        glDeleteBuffers(1, &sceneAxisColorBuffer);
        glDeleteVertexArrays(1, &sceneAxisVertexArrayObj);
    }
    void drawAxis()
    {
        glBindVertexArray(sceneAxisVertexArrayObj);
        glDrawArrays(GL_LINES, 0, 6*3);
        glPointSize(5);
        glBindVertexArray(sceneAxisEndVertexArrayObj);
        glDrawArrays(GL_POINTS, 0, 3*3);
        glPointSize(1);
        glBindVertexArray(0);
    }
}