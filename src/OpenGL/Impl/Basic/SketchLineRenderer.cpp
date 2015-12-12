// Shipeng Xu
// billhsu.x@gmail.com

#include "SketchLineRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"

#define MAX_NUM_VERTEX 1024
namespace SketchLineRenderer {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct vboInfo;
    GLSLShader sketchShader;
    float positionBuffer[MAX_NUM_VERTEX * 3];
    float directionBuffer[MAX_NUM_VERTEX];
    float nextBuffer[MAX_NUM_VERTEX * 3];
    float previousBuffer[MAX_NUM_VERTEX * 3];

    void init() {
        sketchShader.loadFromFile(GL_VERTEX_SHADER, "Shader/shetchLine.vs");
        sketchShader.loadFromFile(GL_FRAGMENT_SHADER, "Shader/sketchLine.fs");
        sketchShader.createProgram();
        vboInfo.vertexBufferSize = 3;
        vboInfo.vertexBufferData = positionBuffer;
        vboInfo.extraBuffer1Size = 1;
        vboInfo.extraBuffer1Data = directionBuffer;
        vboInfo.extraBuffer2Size = 3;
        vboInfo.extraBuffer2Data = previousBuffer;
        vboInfo.extraBuffer3Size = 3;
        vboInfo.extraBuffer3Data = nextBuffer;
        buffer.initVBO(vboInfo, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_1 |
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_2 |
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_3);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        buffer.setVBOLocation(HardwareBuffer::FLAG_EXTRA_BUFFER_1, 1);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_EXTRA_BUFFER_1, 1);
        buffer.setVBOLocation(HardwareBuffer::FLAG_EXTRA_BUFFER_2, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_EXTRA_BUFFER_2, 3);
        buffer.setVBOLocation(HardwareBuffer::FLAG_EXTRA_BUFFER_3, 3);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_EXTRA_BUFFER_1, 3);
    }
    void render(SketchLine sketchLine, Vector3 color) {
        sketchShader.bind();
    }
    void release() {
    }
}