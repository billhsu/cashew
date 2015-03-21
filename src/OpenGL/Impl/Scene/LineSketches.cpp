// Shipeng Xu
// billhsu.x@gmail.com

#include "LineSketches.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"

namespace Scene{
    void renderSketchLines(void* data)
    {
        LineSegmentRenderer::getLineSegmentShader()->bind();
        
        GLuint local_modelView = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE, Controller::modelView.get());
        GLuint local_projection = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE, Controller::projection.get());
        GLuint local_thickness = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "thickness");
        glUniform1f(local_thickness, 0.25f);
        GLuint local_lineColor = glGetUniformLocation(LineSegmentRenderer::getLineSegmentShader()->getProgram(), "lineColor");
        glUniform4f(local_lineColor, 0.443, 0.129, 1.0, 0.9f);
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
}