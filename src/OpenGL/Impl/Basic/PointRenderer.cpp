// Shipeng Xu
// billhsu.x@gmail.com

#include "PointRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"

namespace PointRenderer
{
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    std::vector<Vector3> pointList;
    float* vertexBufferData = NULL;
    
    GLSLShader pointProgram;
    float* mapVectorToArray(const std::vector<Vector3>& list)
    {
        float* result = new float[list.size() * 3];
        for(int i=0; i < list.size(); ++i)
        {
            result[3 * i + 0] = list[i].x;
            result[3 * i + 1] = list[i].y;
            result[3 * i + 2] = list[i].z;
        }
        return result;
    }
    void generateVertexBuffer()
    {
        if(vertexBufferData != NULL)
        {
            delete[] vertexBufferData;
            vertexBufferData = NULL;
        }
        vertexBufferData = mapVectorToArray(pointList);
    }
    void prepareRenderData()
    {
        pointList.clear();
        pointList.push_back(Vector3(0,0,0));
        
        generateVertexBuffer();
        
        VBOInfo.vertexBufferSize = static_cast<int>(pointList.size()) * 3;
        VBOInfo.vertexBufferData = vertexBufferData;
        
        buffer.initVBO(VBOInfo, HardwareBuffer::FLAG_VERTEX_BUFFER);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        
        pointProgram.loadFromFile(GL_VERTEX_SHADER,   "Shader/point.vs");
        pointProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/point.fs");
        pointProgram.loadFromFile(GL_GEOMETRY_SHADER, "Shader/point.gs");
        pointProgram.createProgram();
        
    }
    void render(uint textureId)
    {
        GLSLShader* preShader = GLSLShader::currentShaderProgramObj;
        pointProgram.bind();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_DEPTH_TEST);
//        glDepthMask(GL_FALSE);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureId);
        generateVertexBuffer();
        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize = static_cast<int>(pointList.size()) * 3;
        
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER);
        buffer.render(GL_POINTS);
        
//        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        pointProgram.unbind();
        
        if(preShader != 0) preShader->bind();
    }
    GLSLShader* getPointShader()
    {
        return &pointProgram;
    }
    std::vector<Vector3>& getPointList()
    {
        return pointList;
    }
    void release()
    {
        if(vertexBufferData != NULL)
        {
            delete[] vertexBufferData;
            vertexBufferData = NULL;
        }
    }
}