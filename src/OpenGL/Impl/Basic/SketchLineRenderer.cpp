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
    // times 2 to duplicate the array
    // this will help generate triangles in rendering
    float positionBuffer[MAX_NUM_VERTEX * 3 * 2];
    float directionBuffer[MAX_NUM_VERTEX * 2];
    float nextBuffer[MAX_NUM_VERTEX * 3 * 2];
    float previousBuffer[MAX_NUM_VERTEX * 3 * 2];
    int indexBuffer[MAX_NUM_VERTEX * 6];
    void updateBuffer(SketchLine sketchLine);
    void updateIndexBuffer(int length);

    void init() {
        sketchShader.loadFromFile(GL_VERTEX_SHADER, "Shader/shetchLine.vs");
        sketchShader.loadFromFile(GL_FRAGMENT_SHADER, "Shader/sketchLine.fs");
        sketchShader.createProgram();
        vboInfo.indexBufferSize = 6;
        vboInfo.indexBufferData = indexBuffer;
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
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_3 |
                                    HardwareBuffer::FLAG_INDEX_BUFFER);
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
        updateBuffer(sketchLine);
        buffer.render(GL_TRIANGLES);
    }

    void updateBuffer(SketchLine sketchLine) {
        int numOfVertex = int(sketchLine.getLineSegments().size() + 1);
        if (numOfVertex > MAX_NUM_VERTEX - 1) {
            numOfVertex = MAX_NUM_VERTEX - 1;
        }
        vboInfo.vertexBufferSize = numOfVertex * 3;
        vboInfo.extraBuffer1Size = numOfVertex;
        vboInfo.extraBuffer2Size = numOfVertex * 3;
        vboInfo.extraBuffer3Size = numOfVertex * 3;
        updateIndexBuffer(numOfVertex);

        buffer.updateVBO(vboInfo, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_1 |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_2 |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_3 |
                                      HardwareBuffer::FLAG_INDEX_BUFFER);
    }

    void updateIndexBuffer(int length) {
        vboInfo.indexBufferSize = length * 6;
        int count = 0, index = 0;
        for (int j = 0; j < length; j++) {
            int i = index;
            indexBuffer[count++] = i + 0;
            indexBuffer[count++] = i + 1;
            indexBuffer[count++] = i + 2;
            indexBuffer[count++] = i + 2;
            indexBuffer[count++] = i + 1;
            indexBuffer[count++] = i + 3;
            index += 2;
        }
    }

    GLSLShader* getShader() {
        return &sketchShader;
    }

    void release() {
    }
}