// Shipeng Xu
// billhsu.x@gmail.com

#include "GLSLShader.h"
#include <iostream>
#include <fstream>
int GLSLShader::currentShaderProgramID = 0;
GLSLShader* GLSLShader::currentShaderProgramObj = 0;

GLSLShader::GLSLShader()
{
    mProgramID=-1;
    mNumShaders = 0;
    mShaders[0] = 0;
    mShaders[1] = 0;
    mShaders[2] = 0;
}

GLSLShader::~GLSLShader()
{
    std::cout<<"~GLSLShader() "<<mProgramID<<std::endl;
    glDeleteProgram(mProgramID);
    mProgramID=-1;
}

void GLSLShader::loadFromFile(GLenum shader_type, const std::string& filename)
{
    std::cout<<"Loading shader file: "<<filename<<std::endl;
    std::ifstream shaderFile(filename);
    if (shaderFile.is_open())
    {
        std::string line, fileContent;
        while ( getline (shaderFile,line) )
        {
            fileContent.append(line);
            fileContent.append("\r\n");
        }
        shaderFile.close();
        loadFromString(shader_type, fileContent);
    }
    else std::cerr << "Unable to open file "<<filename<<std::endl;
}

void GLSLShader::loadFromString(GLenum shader_type, const std::string& shaderContent)
{
    GLuint shader = glCreateShader(shader_type);
    
    const char * ptmp = shaderContent.c_str();
    glShaderSource (shader, 1, &ptmp, NULL);
    
    GLint status;
    glCompileShader (shader);
    glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog= new GLchar[infoLogLength];
        glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
        std::cerr<<"Compile log: "<<infoLog<<std::endl;
        delete [] infoLog;
    }
    mShaders[mNumShaders++]=shader;
}

void GLSLShader::createProgram()
{
    mProgramID = glCreateProgram ();
    for(int i=0; i<mNumShaders; ++i)
    {
        if (mShaders[i] != 0) {
            glAttachShader (mProgramID, mShaders[i]);
        }
    }
    
    GLint status;
    glLinkProgram (mProgramID);
    glGetProgramiv (mProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        
        glGetProgramiv (mProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog= new GLchar[infoLogLength];
        glGetProgramInfoLog (mProgramID, infoLogLength, NULL, infoLog);
        std::cerr<<"Link log: "<<infoLog<<std::endl;
        delete [] infoLog;
    }
    for(int i=0; i<mNumShaders; ++i)
    {
        glDeleteShader(mShaders[i]);
    }
    std::cout<<"createProgram() "<<mProgramID<<std::endl;
}

void GLSLShader::bind() {
    glUseProgram(mProgramID);
    currentShaderProgramID = mProgramID;
    currentShaderProgramObj = this;
}
void GLSLShader::unbind() {
    glUseProgram(0);
    currentShaderProgramID = 0;
    currentShaderProgramObj = 0;
}