// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#import <OpenGL/gl3.h>
#include <string>
class GLSLShader
{
public:
    GLSLShader();
    ~GLSLShader();
    void loadFromFile(GLenum shader_type, const std::string& filename);
    void loadFromString(GLenum shader_type, const std::string& shaderContent);
    void createProgram();
    void bind();
    void unbind();
    GLuint getProgram() {return mProgramID;}
    static int currentShaderProgramID;
    static GLSLShader* currentShaderProgramObj;
private:
    GLuint mProgramID;
    GLuint mShaders[3];
    int mNumShaders;
};