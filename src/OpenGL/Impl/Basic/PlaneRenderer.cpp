// Shipeng Xu
// billhsu.x@gmail.com

#include "PlaneRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"
namespace PlaneRenderer {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    float vertexBufferData[12];
    float colorBufferData[16];
    int indexBufferData[6];
    GLSLShader program_plane;

    HardwareBuffer gridBuffer;
    HardwareBuffer::VBOStruct gridVBOInfo;

#define MAX_GRID_SIZE 100
    float gridVertexBufferData[MAX_GRID_SIZE * 4 * 3];
    float gridColorBufferData[MAX_GRID_SIZE * 4 * 4];

    void init() {
        indexBufferData[0] = 0;
        indexBufferData[1] = 1;
        indexBufferData[2] = 2;

        indexBufferData[3] = 0;
        indexBufferData[4] = 2;
        indexBufferData[5] = 3;

        VBOInfo.vertexBufferSize = sizeof(vertexBufferData) / sizeof(float);
        VBOInfo.vertexBufferData = vertexBufferData;
        VBOInfo.colorBufferSize = sizeof(colorBufferData) / sizeof(float);
        VBOInfo.colorBufferData = colorBufferData;
        VBOInfo.indexBufferSize = sizeof(indexBufferData) / sizeof(int);
        VBOInfo.indexBufferData = indexBufferData;

        unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER |
                             HardwareBuffer::FLAG_COLOR_BUFFER |
                             HardwareBuffer::FLAG_INDEX_BUFFER;

        buffer.initVBO(VBOInfo, flags);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOLocation(HardwareBuffer::FLAG_COLOR_BUFFER, 1);

        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_COLOR_BUFFER, 4);

        program_plane.loadFromFile(GL_VERTEX_SHADER, "Shader/plane.vs");
        program_plane.loadFromFile(GL_FRAGMENT_SHADER, "Shader/plane.fs");
        program_plane.createProgram();

        gridVBOInfo.vertexBufferSize = 3;
        gridVBOInfo.vertexBufferData = gridVertexBufferData;
        gridVBOInfo.colorBufferSize = 4;
        gridVBOInfo.colorBufferData = gridColorBufferData;

        unsigned int gridFlags = HardwareBuffer::FLAG_VERTEX_BUFFER |
                                 HardwareBuffer::FLAG_COLOR_BUFFER;

        gridBuffer.initVBO(gridVBOInfo, gridFlags);
        gridBuffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        gridBuffer.setVBOLocation(HardwareBuffer::FLAG_COLOR_BUFFER, 1);

        gridBuffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        gridBuffer.setVBOUnitSize(HardwareBuffer::FLAG_COLOR_BUFFER, 4);
    }
    void render(Plane p, Vector3 center, float size, Vector4 color) {
        // ^ y
        // p4  |  p1
        // |
        // --------> x
        // |
        // p3  |  p2
        program_plane.bind();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        float mR = color.r;
        float mG = color.g;
        float mB = color.b;
        float mAlpha = color.a;
        colorBufferData[0] = mR;
        colorBufferData[1] = mG;
        colorBufferData[2] = mB;
        colorBufferData[3] = mAlpha;
        colorBufferData[4] = mR;
        colorBufferData[5] = mG;
        colorBufferData[6] = mB;
        colorBufferData[7] = mAlpha;
        colorBufferData[8] = mR;
        colorBufferData[9] = mG;
        colorBufferData[10] = mB;
        colorBufferData[11] = mAlpha;
        colorBufferData[12] = mR;
        colorBufferData[13] = mG;
        colorBufferData[14] = mB;
        colorBufferData[15] = mAlpha;

        size /= 2.0f;
        Vector3 randVec = Vector3(0, 0, 1);
        if (randVec.cross(p.N).length() < 0.001f)
            randVec = Vector3(1, 0, 0);
        Vector3 vx = p.N.cross(randVec);
        Vector3 vy = p.N.cross(vx);
        vx.normalize();
        vy.normalize();
        vx *= size;
        vy *= size;

        Vector3 p1, p2, p3, p4;
        p1 = center + vx + vy;
        p2 = center + vx - vy;
        p3 = center - vx - vy;
        p4 = center - vx + vy;

        vertexBufferData[0] = p1.x;
        vertexBufferData[1] = p1.y;
        vertexBufferData[2] = p1.z;
        vertexBufferData[3] = p2.x;
        vertexBufferData[4] = p2.y;
        vertexBufferData[5] = p3.z;
        vertexBufferData[6] = p3.x;
        vertexBufferData[7] = p3.y;
        vertexBufferData[8] = p3.z;
        vertexBufferData[9] = p4.x;
        vertexBufferData[10] = p4.y;
        vertexBufferData[11] = p4.z;

        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize = sizeof(vertexBufferData) / sizeof(float);
        _VBO.colorBufferData = colorBufferData;
        _VBO.colorBufferSize = sizeof(colorBufferData) / sizeof(float);
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                   HardwareBuffer::FLAG_COLOR_BUFFER);
        buffer.render();

        // render the grid
        int grid_size = size * 2;
        if (grid_size > MAX_GRID_SIZE)
            grid_size = MAX_GRID_SIZE;

        for (int i = 0; i <= grid_size; ++i) {
            Vector3 vXinter1 = p1 * ((float)i / (float)grid_size) +
                               p2 * ((float)(grid_size - i) / (float)grid_size);
            Vector3 vXinter2 = p4 * ((float)i / (float)grid_size) +
                               p3 * ((float)(grid_size - i) / (float)grid_size);

            Vector3 vYinter1 = p1 * ((float)i / (float)grid_size) +
                               p4 * ((float)(grid_size - i) / (float)grid_size);
            Vector3 vYinter2 = p2 * ((float)i / (float)grid_size) +
                               p3 * ((float)(grid_size - i) / (float)grid_size);
            gridVertexBufferData[i * 4 * 3 + 0] = vXinter1.x;
            gridVertexBufferData[i * 4 * 3 + 1] = vXinter1.y;
            gridVertexBufferData[i * 4 * 3 + 2] = vXinter1.z;

            gridVertexBufferData[i * 4 * 3 + 3] = vXinter2.x;
            gridVertexBufferData[i * 4 * 3 + 4] = vXinter2.y;
            gridVertexBufferData[i * 4 * 3 + 5] = vXinter2.z;

            gridVertexBufferData[i * 4 * 3 + 6] = vYinter1.x;
            gridVertexBufferData[i * 4 * 3 + 7] = vYinter1.y;
            gridVertexBufferData[i * 4 * 3 + 8] = vYinter1.z;

            gridVertexBufferData[i * 4 * 3 + 9] = vYinter2.x;
            gridVertexBufferData[i * 4 * 3 + 10] = vYinter2.y;
            gridVertexBufferData[i * 4 * 3 + 11] = vYinter2.z;
            for (int j = 0; j < 4; ++j) {
                gridColorBufferData[i * 4 * 4 + j * 4 + 0] = 1.0f;
                gridColorBufferData[i * 4 * 4 + j * 4 + 1] = 1.0f;
                gridColorBufferData[i * 4 * 4 + j * 4 + 2] = 1.0f;
                gridColorBufferData[i * 4 * 4 + j * 4 + 3] = 0.9f;
            }
            if (i == grid_size / 2) {
                for (int j = 0; j < 2; ++j) {
                    gridColorBufferData[i * 4 * 4 + j * 4 + 0] = 1.0f;
                    gridColorBufferData[i * 4 * 4 + j * 4 + 1] = 0.0f;
                    gridColorBufferData[i * 4 * 4 + j * 4 + 2] = 0.0f;
                    gridColorBufferData[i * 4 * 4 + j * 4 + 3] = 0.9f;
                }
                for (int j = 2; j < 4; ++j) {
                    gridColorBufferData[i * 4 * 4 + j * 4 + 0] = 0.0f;
                    gridColorBufferData[i * 4 * 4 + j * 4 + 1] = 0.0f;
                    gridColorBufferData[i * 4 * 4 + j * 4 + 2] = 1.0f;
                    gridColorBufferData[i * 4 * 4 + j * 4 + 3] = 0.9f;
                }
            }
        }
        HardwareBuffer::VBOStruct _gridVBO;
        _gridVBO.vertexBufferData = gridVertexBufferData;
        _gridVBO.vertexBufferSize = grid_size * 4 * 3;
        _gridVBO.colorBufferData = gridColorBufferData;
        _gridVBO.colorBufferSize = grid_size * 4 * 4;
        gridBuffer.updateVBO(_gridVBO, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                           HardwareBuffer::FLAG_COLOR_BUFFER);
        gridBuffer.render(GL_LINES);
        glDisable(GL_BLEND);
        program_plane.unbind();
    }
    GLSLShader* getPlaneShader() {
        return &program_plane;
    }
}