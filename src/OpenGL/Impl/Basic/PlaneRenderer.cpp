// Shipeng Xu
// billhsu.x@gmail.com

#include "PlaneRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"
namespace PlaneRenderer
{
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    float vertexBufferData[12];
    float colorBufferData[16];
    int indexBufferData[6];
    GLSLShader program_plane;

    void prepareRenderData()
    {
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

        unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER
        | HardwareBuffer::FLAG_COLOR_BUFFER
        | HardwareBuffer::FLAG_INDEX_BUFFER;
        
        buffer.initVBO(VBOInfo, flags);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOLocation(HardwareBuffer::FLAG_COLOR_BUFFER, 1);
        
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_COLOR_BUFFER, 4);

        program_plane.loadFromFile(GL_VERTEX_SHADER,   "Shader/plane.vs");
        program_plane.loadFromFile(GL_FRAGMENT_SHADER, "Shader/plane.fs");
        program_plane.createProgram();
    }
    void render(Plane p, Vector3 center, float size, Vector4 color)
    {
        // ^ y
        // p4  |  p1
        // |
        // --------> x
        // |
        // p3  |  p2
        GLSLShader* preShader = GLSLShader::currentShaderProgramObj;
        program_plane.bind();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        float mR = color.r;
        float mG = color.g;
        float mB = color.b;
        float mAlpha = color.a;
        colorBufferData[ 0] = mR; colorBufferData[ 1] = mG;  colorBufferData[ 2] = mB; colorBufferData[ 3] = mAlpha;
        colorBufferData[ 4] = mR; colorBufferData[ 5] = mG;  colorBufferData[ 6] = mB; colorBufferData[ 7] = mAlpha;
        colorBufferData[ 8] = mR; colorBufferData[ 9] = mG;  colorBufferData[10] = mB; colorBufferData[11] = mAlpha;
        colorBufferData[12] = mR; colorBufferData[13] = mG;  colorBufferData[14] = mB; colorBufferData[15] = mAlpha;

        size/=2.0f;
        Vector3 randVec = Vector3(0,0,1);
        if (randVec.cross(p.N).length()<0.001f) randVec = Vector3(1,0,0);
        Vector3 vx = p.N.cross(randVec);
        Vector3 vy = p.N.cross(vx);
        vx.normalize();
        vy.normalize();
        vx*=size;
        vy*=size;
        
        Vector3 p1,p2,p3,p4;
        p1 = center + vx + vy;
        p2 = center + vx - vy;
        p3 = center - vx - vy;
        p4 = center - vx + vy;
        
        vertexBufferData[0] = p1.x; vertexBufferData[ 1] = p1.y; vertexBufferData[ 2] = p1.z;
        vertexBufferData[3] = p2.x; vertexBufferData[ 4] = p2.y; vertexBufferData[ 5] = p3.z;
        vertexBufferData[6] = p3.x; vertexBufferData[ 7] = p3.y; vertexBufferData[ 8] = p3.z;
        vertexBufferData[9] = p4.x; vertexBufferData[10] = p4.y; vertexBufferData[11] = p4.z;

        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize = sizeof(vertexBufferData) / sizeof(float);
        _VBO.colorBufferData = colorBufferData;
        _VBO.colorBufferSize = sizeof(colorBufferData) / sizeof(float);
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER|HardwareBuffer::FLAG_COLOR_BUFFER);
        buffer.render();
        glDisable(GL_BLEND);
        program_plane.unbind();
        
        if(preShader != 0) preShader->bind();
    }
    GLSLShader* getPlaneShader()
    {
        return &program_plane;
    }
}