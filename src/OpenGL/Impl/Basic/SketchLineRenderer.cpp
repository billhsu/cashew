// Shipeng Xu
// billhsu.x@gmail.com

#import <OpenGL/gl3.h>
#include "Core/Controller/Controller.h"
#include "Core/Util/Utility.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "SketchLineRenderer.h"

#define MAX_NUM_VERTEX 1024
namespace SketchLineRenderer {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct vboInfo;
    GLSLShader sketchShader;
    // times 2 to duplicate the array
    // this will help generate triangles in rendering
    float positionBuffer[MAX_NUM_VERTEX * 3 * 2];
    float lineInfoBuffer[MAX_NUM_VERTEX * 3 * 2];
    float nextBuffer[MAX_NUM_VERTEX * 3 * 2];
    float previousBuffer[MAX_NUM_VERTEX * 3 * 2];
    int indexBuffer[MAX_NUM_VERTEX * 6];
    void updateBuffer(SketchLine& sketchLine);
    void updateIndexBuffer(int length);

    void init() {
        sketchShader.loadFromFile(GL_VERTEX_SHADER, "Shader/sketchLine.vs");
        sketchShader.loadFromFile(GL_FRAGMENT_SHADER, "Shader/sketchLine.fs");
        sketchShader.createProgram();
        vboInfo.indexBufferData = indexBuffer;
        vboInfo.vertexBufferData = positionBuffer;
        vboInfo.extraBuffer1Data = lineInfoBuffer;
        vboInfo.extraBuffer2Data = previousBuffer;
        vboInfo.extraBuffer3Data = nextBuffer;
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        buffer.setVBOLocation(HardwareBuffer::FLAG_EXTRA_BUFFER_1, 1);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_EXTRA_BUFFER_1, 3);
        buffer.setVBOLocation(HardwareBuffer::FLAG_EXTRA_BUFFER_2, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_EXTRA_BUFFER_2, 3);
        buffer.setVBOLocation(HardwareBuffer::FLAG_EXTRA_BUFFER_3, 3);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_EXTRA_BUFFER_3, 3);
        buffer.initVBO(vboInfo, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_1 |
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_2 |
                                    HardwareBuffer::FLAG_EXTRA_BUFFER_3 |
                                    HardwareBuffer::FLAG_INDEX_BUFFER);
    }
    void render(SketchLine sketchLine, Vector3 color) {
        if (sketchLine.getLineSegments().size() == 0) {
            return;
        }
        sketchShader.bind();
        GLuint local_modelView =
            glGetUniformLocation(sketchShader.getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                           Controller::modelView.get());
        GLuint local_projection =
            glGetUniformLocation(sketchShader.getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                           Controller::projection.get());
        GLuint local_color =
            glGetUniformLocation(sketchShader.getProgram(), "color");
        glUniform3fv(local_color, 1, color.cell);
        GLuint local_aspect =
            glGetUniformLocation(sketchShader.getProgram(), "aspect");
        glUniform1f(local_aspect,
                    Controller::windowWidth / Controller::windowHeight);
        GLuint local_thickness =
            glGetUniformLocation(sketchShader.getProgram(), "thickness");
        glUniform1f(local_thickness, 1.0f);
        updateBuffer(sketchLine);
        buffer.render(GL_TRIANGLES);
    }

    void setFloatArrayFromVector(float* arrayStartPtr, Vector3 position) {
        arrayStartPtr[0] = position.x;
        arrayStartPtr[1] = position.y;
        arrayStartPtr[2] = position.z;
    }

    void updateBuffer(SketchLine& sketchLine) {
        // This is a speciel case.
        // Let's break the line segment into two half line segments.
        if (sketchLine.getLineSegments().size() == 1) {
            Vector3 originalEnd = sketchLine.getLineSegments()[0].points[1];
            Vector3 originBegin = sketchLine.getLineSegments()[0].points[0];
            Vector3 centerPos = 0.5f * (originBegin + originalEnd);
            sketchLine.getLineSegments()[0].points[1] = centerPos;
            sketchLine.addLineSegment(LineSegment(centerPos, originalEnd));
        }
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
        vboInfo.extraBuffer1Size = numOfVertex * 3 * 2;
        vboInfo.extraBuffer2Size = numOfVertex * 3 * 2;
        vboInfo.extraBuffer3Size = numOfVertex * 3 * 2;
        updateIndexBuffer(numOfVertex);
        float totalDistance = 0.0f;
        float runningDistance = 0.0f;
        // calculate the total distance of the sketch line
        for (int i = 0; i < sketchLine.getLineSegments().size(); ++i) {
            totalDistance += sketchLine.getLineSegments()[i].length();
        }
        float widthMin = 0.1f;
        float widthMax = 2.0f;
        float widthSmooth = widthMin;

        LineSegment firstLineSegment = sketchLine.getLineSegments()[0];
        setFloatArrayFromVector(&positionBuffer[0], firstLineSegment.points[0]);
        setFloatArrayFromVector(&positionBuffer[3], firstLineSegment.points[0]);
        setFloatArrayFromVector(&previousBuffer[0], firstLineSegment.points[0]);
        setFloatArrayFromVector(&previousBuffer[3], firstLineSegment.points[0]);
        setFloatArrayFromVector(&nextBuffer[0], firstLineSegment.points[1]);
        setFloatArrayFromVector(&nextBuffer[3], firstLineSegment.points[1]);
        setFloatArrayFromVector(&lineInfoBuffer[0], Vector3(0, 0, 0));
        setFloatArrayFromVector(&lineInfoBuffer[3], Vector3(0, 0, 0));
        const float targetLength = 1.0f;
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

            runningDistance += preLineSegment.length();
            float widthScale = 1.0f;
            if (runningDistance <= targetLength) {
                widthScale = runningDistance / targetLength;
            } else if ((totalDistance - runningDistance) <= targetLength) {
                widthScale = (totalDistance - runningDistance) / targetLength;
            }
            float widthPct =
                mapValueWithRange(preLineSegment.length(), 1, 0.7, 0, 1, true);
            widthSmooth = 0.85f * widthSmooth +
                          0.15 * mapValueWithRange(powf(widthPct, 3.4), 0, 1,
                                                   widthMin, widthMax, true);
            setFloatArrayFromVector(&lineInfoBuffer[6 * i + 0],
                                    Vector3(-widthSmooth * widthScale, 0, 0));
            setFloatArrayFromVector(&lineInfoBuffer[6 * i + 3],
                                    Vector3(widthSmooth * widthScale, 0, 0));
        }
        int lastVertexIdx = numOfVertex - 1;
        LineSegment lastLineSegment =
            sketchLine.getLineSegments()[lastVertexIdx - 1];
        float widthPct =
            mapValueWithRange(lastLineSegment.length(), 0.0, 0.7, 0, 1, true);
        widthSmooth = 0.85f * widthSmooth +
                      0.15 * mapValueWithRange(powf(widthPct, 3.4), 0, 1,
                                               widthMin, widthMax, true);
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
        setFloatArrayFromVector(&lineInfoBuffer[6 * lastVertexIdx + 0],
                                Vector3(0, 0, 0));
        setFloatArrayFromVector(&lineInfoBuffer[6 * lastVertexIdx + 3],
                                Vector3(0, 0, 0));
        buffer.updateVBO(vboInfo, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_1 |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_2 |
                                      HardwareBuffer::FLAG_EXTRA_BUFFER_3 |
                                      HardwareBuffer::FLAG_INDEX_BUFFER);
    }

    void updateIndexBuffer(int length) {
        static int previousLength = 0;
        vboInfo.indexBufferSize = (length - 1) * 6;
        int count = 0, index = 0;
        for (int j = 0; j < length - 1; j++) {
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