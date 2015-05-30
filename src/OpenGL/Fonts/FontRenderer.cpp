// Shipeng Xu
// billhsu.x@gmail.com
#include "FontRenderer.h"
#include "Core/Math/Vectors.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include "OpenGL/Shader/GLSLShader.h"
#define MAX_BUFFER_SIZE 2048
namespace FontRenderer {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    
    float vertexBufferData[MAX_BUFFER_SIZE];
    float uvBufferData[MAX_BUFFER_SIZE];
    struct sth_stash* stash;
    std::map <std::string, int> fontList;
    std::vector<TextRenderInfo> textRenderInfoList;
    
    void prepareRenderData() {
        fontList.clear();
        stash = sth_create(512, 512);
        std::cout<<"Loading fonts.."<<std::endl;
        int font = sth_add_font(stash, "media/fonts/droid-sans/DroidSans.ttf");
        fontList["DroidSans"] = font;
        std::cout<<"DroidSans "<<font<<std::endl;
        font = sth_add_font(stash, "media/fonts/droid-sans/DroidSans-Bold.ttf");
        fontList["DroidSans-Bold"] = font;
        std::cout<<"DroidSans-Bold "<<font<<std::endl;
        
        VBOInfo.vertexBufferSize = 2;
        VBOInfo.vertexBufferData = vertexBufferData;
        VBOInfo.uvBufferSize = 1;
        VBOInfo.uvBufferData = uvBufferData;
        unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER
        | HardwareBuffer::FLAG_UV_BUFFER;
        
        buffer.initVBO(VBOInfo, flags);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOLocation(HardwareBuffer::FLAG_UV_BUFFER, 1);
        
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_UV_BUFFER, 2);
    }
    
    void addText(int fontId, float fontSize, float x, float y, std::string content) {
        TextRenderInfo textRenderInfo;
        textRenderInfo.fontId = fontId;
        textRenderInfo.fontSize = fontSize;
        textRenderInfo.x = x;
        textRenderInfo.y = y;
        textRenderInfo.content = content;
        textRenderInfoList.push_back(textRenderInfo);
    }
    
    void render() {
        sth_begin_draw(stash);
        for(int i=0; i<textRenderInfoList.size(); ++i) {
            sth_draw_text(stash, textRenderInfoList[i].fontId,
                          textRenderInfoList[i].fontSize,
                          textRenderInfoList[i].x,
                          textRenderInfoList[i].y,
                          textRenderInfoList[i].content.c_str(),
                          &textRenderInfoList[i].x);
        }
        sth_end_draw(stash);
        textRenderInfoList.clear();
    }
    
    void flushDraw(sth_texture* texture) {
        int nvert = texture->nverts;
        for(int i=0; i<nvert; ++i) {
            if(i%4 == 0 || i%4 ==1) {
                vertexBufferData[i/4 + i%4] = texture->verts[i];
            } else {
                uvBufferData[i/4 + i%4 - 2] = texture->verts[i];
            }
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize = nvert/2;
        _VBO.uvBufferData = uvBufferData;
        _VBO.uvBufferSize = nvert/2;
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER | HardwareBuffer::FLAG_UV_BUFFER);
        buffer.render();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void release() {
        sth_delete(stash);
    }

}
