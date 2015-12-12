// Shipeng Xu
// billhsu.x@gmail.com

#include "SketchLineRenderer.h"
#import <OpenGL/gl3.h>
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
        sketchShader.loadFromFile(GL_VERTEX_SHADER, "Shader/sketchLine.vs");
        sketchShader.loadFromFile(GL_FRAGMENT_SHADER, "Shader/sketchLine.fs");
        sketchShader.createProgram();
        vboInfo.indexBufferSize = 6;
        vboInfo.indexBufferData = indexBuffer;
        vboInfo.vertexBufferSize = 3 * 2;
        vboInfo.vertexBufferData = positionBuffer;
        vboInfo.extraBuffer1Size = 1 * 2;
        vboInfo.extraBuffer1Data = directionBuffer;
        vboInfo.extraBuffer2Size = 3 * 2;
        vboInfo.extraBuffer2Data = previousBuffer;
        vboInfo.extraBuffer3Size = 3 * 2;
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
        GLuint local_color =
            glGetUniformLocation(sketchShader.getProgram(), "color");
        glUniform3fv(local_color, 1, color.cell);
        updateBuffer(sketchLine);
        buffer.render(GL_TRIANGLES);
    }

    void setFloatArrayFromVector(float* arrayStartPtr, Vector3 position) {
        arrayStartPtr[0] = position.x;
        arrayStartPtr[1] = position.y;
        arrayStartPtr[2] = position.z;
    }

    void updateBuffer(SketchLine sketchLine) {
        int numOfVertex = int(sketchLine.getLineSegments().size() + 1);
        if (numOfVertex > MAX_NUM_VERTEX - 1) {
            numOfVertex = MAX_NUM_VERTEX - 1;
        }
        if (numOfVertex == 0) {
            return;
        }
        // times 2 to duplicate the array
        // this will help generate triangles in rendering
        vboInfo.vertexBufferSize = numOfVertex * 3 * 2;
        vboInfo.extraBuffer1Size = numOfVertex * 2;
        vboInfo.extraBuffer2Size = numOfVertex * 3 * 2;
        vboInfo.extraBuffer3Size = numOfVertex * 3 * 2;
        updateIndexBuffer(numOfVertex);
        LineSegment firstLineSegment = sketchLine.getLineSegments()[0];
        setFloatArrayFromVector(&positionBuffer[0], firstLineSegment.points[0]);
        setFloatArrayFromVector(&positionBuffer[3], firstLineSegment.points[0]);
        setFloatArrayFromVector(&previousBuffer[0], firstLineSegment.points[0]);
        setFloatArrayFromVector(&previousBuffer[3], firstLineSegment.points[0]);
        setFloatArrayFromVector(&nextBuffer[0], firstLineSegment.points[1]);
        setFloatArrayFromVector(&nextBuffer[3], firstLineSegment.points[1]);
        directionBuffer[0] = -1.0f;
        directionBuffer[1] = 1.0f;
        for (int i = 1; i < numOfVertex - 1; ++i) {
            LineSegment preLineSegment = sketchLine.getLineSegments()[i - 1];
            LineSegment lineSegment = sketchLine.getLineSegments()[i];
            setFloatArrayFromVector(&positionBuffer[6 * i + 0],
                                    lineSegment.points[0]);
            setFloatArrayFromVector(&positionBuffer[6 * i + 3],
                                    lineSegment.points[0]);
            setFloatArrayFromVector(&previousBuffer[6 * i + 0],
                                    preLineSegment.points[0]);
            setFloatArrayFromVector(&previousBuffer[6 * i + 3],
                                    preLineSegment.points[0]);
            setFloatArrayFromVector(&nextBuffer[6 * i + 0],
                                    lineSegment.points[1]);
            setFloatArrayFromVector(&nextBuffer[6 * i + 3],
                                    lineSegment.points[1]);
            directionBuffer[2 * i + 0] = -1.0f;
            directionBuffer[2 * i + 1] = 1.0f;
        }
        int lastVertexIdx = numOfVertex - 1;
        LineSegment lastLineSegment =
            sketchLine.getLineSegments()[lastVertexIdx - 1];
        setFloatArrayFromVector(&positionBuffer[6 * lastVertexIdx + 0],
                                lastLineSegment.points[1]);
        setFloatArrayFromVector(&positionBuffer[6 * lastVertexIdx + 3],
                                lastLineSegment.points[1]);
        setFloatArrayFromVector(&previousBuffer[6 * lastVertexIdx + 0],
                                lastLineSegment.points[0]);
        setFloatArrayFromVector(&previousBuffer[6 * lastVertexIdx + 3],
                                lastLineSegment.points[0]);
        setFloatArrayFromVector(&nextBuffer[6 * lastVertexIdx + 0],
                                lastLineSegment.points[1]);
        setFloatArrayFromVector(&nextBuffer[6 * lastVertexIdx + 3],
                                lastLineSegment.points[1]);
        directionBuffer[2 * lastVertexIdx + 0] = -1.0f;
        directionBuffer[2 * lastVertexIdx + 1] = 1.0f;
        buffer.updateVBO(vboInfo, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_1 |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_2 |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_3 |
                                      HardwareBuffer::FLAG_INDEX_BUFFER);
    }

    void updateIndexBuffer(int length) {
        static int previousLength = 0;
        // no need to update the index array if the previous length is longer
        // than the current one.
        if (length < previousLength) {
            return;
        }
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
        previousLength = length;
    }

    GLSLShader* getShader() {
        return &sketchShader;
    }

    void release() {
    }
}