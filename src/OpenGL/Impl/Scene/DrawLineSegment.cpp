// Shipeng Xu
// billhsu.x@gmail.com

#include "DrawLineSegment.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "Core/Math/Vectors.h"
#include "Core/Basic/LineSegment.h"
#include "Core/Basic/SketchLine.h"

namespace Scene {
    void renderLineSegmentsMode(bool wireframe) {
        LineSegmentRenderer::getLineSegmentShader()->bind();

        GLuint local_modelView = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                           Controller::modelView.get());
        GLuint local_projection = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                           Controller::projection.get());
        GLuint local_thickness = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "thickness");
        glUniform1f(local_thickness, 0.1f);
        GLuint local_lineColor = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "lineColor");
        if (LineSegmentRenderer::getLineSegmentList().size() > 0) {
            if (!wireframe) {
                glUniform4f(local_lineColor, 0.545, 0.2, 1, 1.0f);
                LineSegmentRenderer::render(0);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDisable(GL_DEPTH_TEST);
                glUniform4f(local_lineColor, 1, 1, 1, 0.5f);
                LineSegmentRenderer::render(0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glEnable(GL_DEPTH_TEST);
            }
        }
    }
    void renderLineSegments(void* data) {
        LineSegmentRenderer::getLineSegmentList().clear();
        for (int i = 0; i < SketchLine::getGlobalLineSegments().size(); ++i) {
            LineSegmentRenderer::getLineSegmentList().push_back(
                SketchLine::getGlobalLineSegments()[i]);
        }
        renderLineSegmentsMode(false);
        renderLineSegmentsMode(true);
    }
    void renderLineSegmentsEndpoints(void* data) {
        PointRenderer::getPointShader()->bind();
        GLuint local_modelView = glGetUniformLocation(
            PointRenderer::getPointShader()->getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                           Controller::modelView.get());
        GLuint local_projection = glGetUniformLocation(
            PointRenderer::getPointShader()->getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                           Controller::projection.get());
        GLuint local_pointSize = glGetUniformLocation(
            PointRenderer::getPointShader()->getProgram(), "pointSize");
        glUniform1f(local_pointSize, 0.2f);
        glUniform1i(
            glGetUniformLocation(PointRenderer::getPointShader()->getProgram(),
                                 "pointTexture"),
            1);
        PointRenderer::getPointList().clear();
        for_each(SketchLine::getGlobalLineSegments().begin(),
                 SketchLine::getGlobalLineSegments().end(), [](LineSegment v) {
                     PointRenderer::getPointList().push_back(v.points[0]);
                     PointRenderer::getPointList().push_back(v.points[1]);
                 });
        if (PointRenderer::getPointList().size() > 0) {
            PointRenderer::render(
                TextureManager::getInstance()
                    .getTexture("media/textures/point_current.png")
                    .glTextureID);
        }
    }

    void renderSingleLineSegment(LineSegment line, Vector4 color,
                                 float thickness) {
        LineSegmentRenderer::getLineSegmentShader()->bind();

        GLuint local_modelView = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                           Controller::modelView.get());
        GLuint local_projection = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                           Controller::projection.get());
        GLuint local_thickness = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "thickness");
        glUniform1f(local_thickness, thickness);
        GLuint local_lineColor = glGetUniformLocation(
            LineSegmentRenderer::getLineSegmentShader()->getProgram(),
            "lineColor");
        glUniform4f(local_lineColor, color.r, color.g, color.b, color.a);
        LineSegmentRenderer::getLineSegmentList().clear();
        LineSegmentRenderer::getLineSegmentList().push_back(line);
        LineSegmentRenderer::render(0);
    }
    void renderSingleSketchLine(SketchLine sketchLine, Vector4 color,
                                float thickness) {
        LineSegmentRenderer::getLineSegmentList().clear();
        for (int i = 0; i < sketchLine.getLineSegments().size(); ++i) {
            LineSegmentRenderer::getLineSegmentList().push_back(
                sketchLine.getLineSegments()[i]);
        }
        renderLineSegmentsMode(false);
        renderLineSegmentsMode(true);
    }
}