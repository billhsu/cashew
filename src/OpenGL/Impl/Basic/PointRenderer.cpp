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
        
        VBOInfo.vertexBufferSize = static_cast<int>(pointList.size());
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
    }
    void bindPointShader()
    {
    }
    void unbindPointShader()
    {
    }
    GLSLShader* getPointShader()
    {
        return &pointProgram;
    }
    std::vector<Vector3>& getPointList()
    {
        return pointList;
    }
}