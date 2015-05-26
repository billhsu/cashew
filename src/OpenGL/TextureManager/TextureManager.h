// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <OpengL/gl3.h>

class TextureManager
{
public:
    static TextureManager& getInstance()
    {
        static TextureManager instance;
        return instance;
    }
    int loadTexture(std::string filename, int channels);
    
    struct TextureInfo
    {
        std::string filename;
        int width, height;
        int channels;
        GLuint glTextureID;
    };
    TextureInfo getTexture(std::string filename);
private:
    TextureManager();
    ~TextureManager();
    std::map<std::string, TextureInfo> textureNameToIdMap;
    typedef std::map<std::string, TextureInfo>::iterator textureNameToIdMapIter;
};