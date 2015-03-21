// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
class GLSLShader;
namespace Scene{
    void prepareSceneAxis(float size);
    void clearScene();
    void prepareSceneGrid(float size, float step);
    void drawScene();
    void drawSceneWrapper(void* data);
    GLSLShader* getSceneShader();
};