// Shipeng Xu
// billhsu.x@gmail.com

#include "LineSketches.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/TextureManager/TextureManager.h"

namespace Scene{
    void renderSketchLines(void* data)
    {
        LineSegmentRenderer::getLineSegmentShader()->bind();
        
        GLuint local_modelView = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE, Controller::modelView.get());
        GLuint local_projection = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE, Controller::projection.get());
        GLuint local_thickness = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "thickness");
        glUniform1f(local_thickness, 0.03f);
        GLuint local_lineColor = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "lineColor");
        glUniform4f(local_lineColor, 0.545, 0.2, 1, 0.9f);
        LineSegmentRenderer::getLineSegmentList().clear();
        for(int i=0; i<Controller::sketchLines.size(); ++i)
        {
            LineSegmentRenderer::getLineSegmentList().push_back(Controller::sketchLines[i]);
        }
        if(LineSegmentRenderer::getLineSegmentList().size() > 0)
        {
            LineSegmentRenderer::render(0);
        }
    }
    void renderSketchLinesEndpoints(void* data)
    {
        PointRenderer::getPointShader()->bind();
        GLuint local_modelView = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE, Controller::modelView.get());
        GLuint local_projection = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE, Controller::projection.get());
        GLuint local_pointSize = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "pointSize");
        glUniform1f(local_pointSize, 0.2f);
        glUniform1i(glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "pointTexture"), 1);
        PointRenderer::getPointList().clear();
        for_each(Controller::sketchLines.begin(), Controller::sketchLines.end(), [](LineSegment v){
            PointRenderer::getPointList().push_back(v.points[0]);
            PointRenderer::getPointList().push_back(v.points[1]);
        });
        if(PointRenderer::getPointList().size()>0)
        {
            PointRenderer::render(TextureManager::getInstance().getTexture("media/textures/point_current.png").glTextureID);
        }
    }
}