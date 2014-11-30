// Shipeng Xu
// billhsu.x@gmail.com

#include "Scene.h"
#import <OpenGL/gl3.h>
#include "Core/Math/Vectors.h"
namespace cashew{
    static float* gridVertex = NULL;
    static float* gridColor = NULL;
    GLuint sceneGridVertexBuffer;
    GLuint sceneGridColorBuffer;
    GLuint sceneGridVertexArrayObj;
    int grid_step_cnt;
    void prepareSceneGrid(float size, float step)
    {
        grid_step_cnt = size / step;
        gridVertex = new float[8 * 3 * grid_step_cnt];
        gridColor = new float[8 * 3 * grid_step_cnt];
        int span = 8 * 3;
        for(int i = 0; i < grid_step_cnt; ++i)
        {
            gridVertex[span * i + 0] = -size;
            gridVertex[span * i + 1] = 0.0f;
            gridVertex[span * i + 2] = (float)i * step;
            
            gridVertex[span * i + 3] = size;
            gridVertex[span * i + 4] = 0.0f;
            gridVertex[span * i + 5] = (float)i * step;
            
            gridVertex[span * i + 6] = -size;
            gridVertex[span * i + 7] = 0.0f;
            gridVertex[span * i + 8] = -(float)i * step;
            
            gridVertex[span * i + 9] = size;
            gridVertex[span * i + 10] = 0.0f;
            gridVertex[span * i + 11] = -(float)i * step;
            
            //////////////////////////////////////////
            
            gridVertex[span * i + 12] = (float)i * step;
            gridVertex[span * i + 13] = 0.0f;
            gridVertex[span * i + 14] = -size;
            
            gridVertex[span * i + 15] = (float)i * step;
            gridVertex[span * i + 16] = 0.0f;
            gridVertex[span * i + 17] = size;
            
            gridVertex[span * i + 18] = -(float)i * step;
            gridVertex[span * i + 19] = 0.0f;
            gridVertex[span * i + 20] = -size;
            
            gridVertex[span * i + 21] = -(float)i * step;
            gridVertex[span * i + 22] = 0.0f;
            gridVertex[span * i + 23] = size;
            
            
            gridColor[span * i + 0] = 0.3f; gridColor[span * i + 1] = 0.3f; gridColor[span * i + 2] = 0.3f;
            gridColor[span * i + 3] = 0.3f; gridColor[span * i + 4] = 0.3f; gridColor[span * i + 5] = 0.3f;
            gridColor[span * i + 6] = 0.3f; gridColor[span * i + 7] = 0.3f; gridColor[span * i + 8] = 0.3f;
            gridColor[span * i + 9] = 0.3f; gridColor[span * i + 10] = 0.3f; gridColor[span * i + 11] = 0.3f;
            
            gridColor[span * i + 12] = 0.3f; gridColor[span * i + 13] = 0.3f; gridColor[span * i + 14] = 0.3f;
            gridColor[span * i + 15] = 0.3f; gridColor[span * i + 16] = 0.3f; gridColor[span * i + 17] = 0.3f;
            gridColor[span * i + 18] = 0.3f; gridColor[span * i + 19] = 0.3f; gridColor[span * i + 20] = 0.3f;
            gridColor[span * i + 21] = 0.3f; gridColor[span * i + 22] = 0.3f; gridColor[span * i + 23] = 0.3f;        }
        glGenBuffers(1, &sceneGridVertexBuffer);
        glGenBuffers(1, &sceneGridColorBuffer);
        glGenVertexArrays(1, &sceneGridVertexArrayObj);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneGridVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 8 * 3 * grid_step_cnt * 4, gridVertex, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneGridColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, 8 * 3 * grid_step_cnt * 4, gridColor, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // create vertex array for shader attributes
        glBindVertexArray(sceneGridVertexArrayObj);
        
        glBindBuffer(GL_ARRAY_BUFFER, sceneGridVertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, sceneGridColorBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }
    void drawGrid()
    {
        glDepthFunc(GL_ALWAYS);
        glBindVertexArray(sceneGridVertexArrayObj);
        glDrawArrays(GL_LINES, 0, 8 * 3 * grid_step_cnt);
        glBindVertexArray(0);
        glDepthFunc(GL_LEQUAL);
    }

    GLuint sceneAxisVertexBuffer;
    GLuint sceneAxisEndVertexBuffer;
    GLuint sceneAxisColorBuffer;
    GLuint sceneAxisEndColorBuffer;
    GLuint sceneAxisVertexArrayObj;
    GLuint sceneAxisEndVertexArrayObj;
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
        
        glDeleteBuffers(1, &sceneAxisEndVertexBuffer);
        glDeleteBuffers(1, &sceneAxisEndColorBuffer);
        glDeleteVertexArrays(1, &sceneAxisEndVertexArrayObj);
        
        glDeleteBuffers(1, &sceneGridVertexBuffer);
        glDeleteBuffers(1, &sceneGridColorBuffer);
        glDeleteVertexArrays(1, &sceneGridVertexArrayObj);
        
        if(gridVertex!=NULL) delete [] gridVertex;
        if(gridColor!=NULL) delete [] gridColor;
    }
    void drawAxis()
    {
        glDepthFunc(GL_ALWAYS);
        glBindVertexArray(sceneAxisVertexArrayObj);
        glLineWidth(3);
        glDrawArrays(GL_LINES, 0, 6*3);
        glLineWidth(1);
        glPointSize(5);
        glBindVertexArray(sceneAxisEndVertexArrayObj);
        glDrawArrays(GL_POINTS, 0, 3*3);
        glPointSize(1);
        glBindVertexArray(0);
        glDepthFunc(GL_LEQUAL);
    }
}