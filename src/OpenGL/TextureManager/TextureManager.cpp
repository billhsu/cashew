// Shipeng Xu
// billhsu.x@gmail.com

#include "TextureManager.h"
#include "stb_image.h"

TextureManager::TextureManager() {
    std::cout << "TextureManager::TextureManager()" << std::endl;
    textureNameToIdMap.clear();
}
TextureManager::~TextureManager() {
    std::cout << "TextureManager::~TextureManager()" << std::endl;
    for (textureNameToIdMapIter it = textureNameToIdMap.begin();
         it != textureNameToIdMap.end(); ++it) {
        std::cout << "Deleting texture ID: " << it->second.glTextureID
                  << std::endl;
        glDeleteTextures(1, &it->second.glTextureID);
    }
}

int TextureManager::loadTexture(std::string filename, int channels) {
    if (getTexture(filename).glTextureID != -1)
        return getTexture(filename).glTextureID;
    std::cout << "TextureManager::loadTexture " << filename << std::endl;
    TextureInfo textureInfo;

    unsigned char* dataBuffer =
        stbi_load(filename.c_str(), &textureInfo.width, &textureInfo.height,
                  &textureInfo.channels, channels);
    if (dataBuffer == NULL)
        return -1;
    textureInfo.filename = filename;
    // Allocate an OpenGL texture
    glGenTextures(1, &textureInfo.glTextureID);
    glBindTexture(GL_TEXTURE_2D, textureInfo.glTextureID);
    std::cout << textureInfo.filename << " ID: " << textureInfo.glTextureID
              << std::endl;

    // Build the image buffer
    glTexImage2D(GL_TEXTURE_2D, 0,
                 (textureInfo.channels == 3) ? GL_RGB8 : GL_RGBA8,
                 textureInfo.width, textureInfo.height, 0,
                 (textureInfo.channels == 3) ? GL_RGB : GL_RGBA,
                 GL_UNSIGNED_BYTE, dataBuffer);

    // Nearest-neighbor (i.e. no smoothing) interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Wrap texture around
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Done setting image parameters
    glDisable(GL_TEXTURE_2D);

    // Release internal buffer
    stbi_image_free(dataBuffer);

    // Save to dictionary
    textureNameToIdMap.insert(
        std::pair<std::string, TextureInfo>(filename, textureInfo));
    int err = glGetError();
    if (err != 0) {
        std::cout << err << std::endl;
    }
    return textureInfo.glTextureID;
}
TextureManager::TextureInfo TextureManager::getTexture(std::string filename) {
    textureNameToIdMapIter it = textureNameToIdMap.find(filename);
    if (it != textureNameToIdMap.end()) {
        return it->second;
    } else {
        TextureInfo empty;
        empty.glTextureID = -1;
        return empty;
    }
}