// Shipeng Xu
// billhsu.x@gmail.com

#include "LineSegmentRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "Core/Basic/LineSegment.h"

namespace LineSegmentRenderer {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    std::vector<LineSegment> lineSegmentList;
    float* vertexBufferData = NULL;

    GLSLShader lineSegmentProgram;
    float* mapVectorToArray(const std::vector<LineSegment>& list) {
        float* result = new float[list.size() * 3 * 2];
        for (int i = 0; i < list.size(); ++i) {
            result[6 * i + 0] = list[i].points[0].x;
            result[6 * i + 1] = list[i].points[0].y;
            result[6 * i + 2] = list[i].points[0].z;

            result[6 * i + 3] = list[i].points[1].x;
            result[6 * i + 4] = list[i].points[1].y;
            result[6 * i + 5] = list[i].points[1].z;
        }
        return result;
    }
    void generateVertexBuffer() {
        if (vertexBufferData != NULL) {
            delete[] vertexBufferData;
            vertexBufferData = NULL;
        }
        vertexBufferData = mapVectorToArray(lineSegmentList);
    }
    void init() {
        lineSegmentList.clear();
        lineSegmentList.push_back(
            LineSegment(Vector3(0, 0, 0), Vector3(0, 0, 0)));

        generateVertexBuffer();

        VBOInfo.vertexBufferSize =
            static_cast<int>(lineSegmentList.size()) * 3 * 2;
        VBOInfo.vertexBufferData = vertexBufferData;

        buffer.initVBO(VBOInfo, HardwareBuffer::FLAG_VERTEX_BUFFER);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);

        lineSegmentProgram.loadFromFile(GL_VERTEX_SHADER,
                                        "Shader/lineSegment.vs");
        lineSegmentProgram.loadFromFile(GL_FRAGMENT_SHADER,
                                        "Shader/lineSegment.fs");
        lineSegmentProgram.loadFromFile(GL_GEOMETRY_SHADER,
                                        "Shader/lineSegment.gs");
        lineSegmentProgram.createProgram();
    }
    void render(uint textureId) {
        lineSegmentProgram.bind();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //        glActiveTexture(GL_TEXTURE1);
        //        glBindTexture(GL_TEXTURE_2D, textureId);
        generateVertexBuffer();
        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize =
            static_cast<int>(lineSegmentList.size()) * 3 * 2;

        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER);
        buffer.render(GL_LINES);

        glDisable(GL_BLEND);
        lineSegmentProgram.unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    GLSLShader* getLineSegmentShader() {
        return &lineSegmentProgram;
    }
    std::vector<LineSegment>& getLineSegmentList() {
        return lineSegmentList;
    }
    void release() {
        if (vertexBufferData != NULL) {
            delete[] vertexBufferData;
            vertexBufferData = NULL;
        }
    }
}