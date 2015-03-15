// Shipeng Xu
// billhsu.x@gmail.com

#include "LineSegmentRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"

namespace LineSegmentRenderer
{
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    std::vector<Vector3> lineSegmentList;
    float* vertexBufferData = NULL;
    
    GLSLShader lineSegmentProgram;
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
        vertexBufferData = mapVectorToArray(lineSegmentList);
    }
    void prepareRenderData()
    {
        lineSegmentList.clear();
        lineSegmentList.push_back(Vector3(0,0,0));
        
        generateVertexBuffer();
        
        VBOInfo.vertexBufferSize = static_cast<int>(lineSegmentList.size()) * 3;
        VBOInfo.vertexBufferData = vertexBufferData;
        
        buffer.initVBO(VBOInfo, HardwareBuffer::FLAG_VERTEX_BUFFER);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 3);
        
        lineSegmentProgram.loadFromFile(GL_VERTEX_SHADER,   "Shader/lineSegment.vs");
        lineSegmentProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/lineSegment.fs");
        lineSegmentProgram.loadFromFile(GL_GEOMETRY_SHADER, "Shader/lineSegment.gs");
        lineSegmentProgram.createProgram();
        
    }
    void render(uint textureId)
    {
        lineSegmentProgram.bind();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureId);
        generateVertexBuffer();
        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize = static_cast<int>(lineSegmentList.size()) * 3;
        
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER);
        buffer.render(GL_POINTS);
        
        glDisable(GL_BLEND);
        lineSegmentProgram.unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    GLSLShader* getLineSegmentShader()
    {
        return &lineSegmentProgram;
    }
    std::vector<Vector3>& getLineSegmentList()
    {
        return lineSegmentList;
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