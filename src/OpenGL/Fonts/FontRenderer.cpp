// Shipeng Xu
// billhsu.x@gmail.com
#include "Core/Math/Vectors.h"
#include "Core/UI/IMGUI.h"
#include "FontRenderer.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include "OpenGL/Shader/GLSLShader.h"
#define MAX_VERT_SIZE 1024

namespace FontRenderer {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    GLSLShader fontProgram;

    float vertexBufferData[MAX_VERT_SIZE * 2];
    float uvBufferData[MAX_VERT_SIZE * 2];
    float colorBufferData[MAX_VERT_SIZE * 3];
    struct sth_stash* stash;
    std::map<std::string, int> fontList;
    std::vector<TextRenderInfo> textRenderInfoList;

    void init() {
        fontList.clear();
        stash = sth_create(512, 512);
        std::cout << "Loading fonts.." << std::endl;
        int font = sth_add_font(stash, "media/fonts/droid-sans/DroidSans.ttf");
        fontList["DroidSans"] = font;
        std::cout << "DroidSans " << font << std::endl;
        font = sth_add_font(stash,
                            "media/fonts/wqy-microhei/WenQuanYiMicroHei.ttf");
        fontList["WenQuanYiMicroHei"] = font;
        std::cout << "WenQuanYiMicroHei " << font << std::endl;

        VBOInfo.vertexBufferData = vertexBufferData;
        VBOInfo.uvBufferData = uvBufferData;
        VBOInfo.colorBufferData = colorBufferData;
        unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER |
                             HardwareBuffer::FLAG_UV_BUFFER |
                             HardwareBuffer::FLAG_COLOR_BUFFER;

        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOLocation(HardwareBuffer::FLAG_UV_BUFFER, 1);
        buffer.setVBOLocation(HardwareBuffer::FLAG_COLOR_BUFFER, 2);

        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_UV_BUFFER, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_COLOR_BUFFER, 3);
        buffer.initVBO(VBOInfo, flags);

        fontProgram.loadFromFile(GL_VERTEX_SHADER, "Shader/font.vs");
        fontProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/font.fs");
        fontProgram.createProgram();
    }

    void addText(int fontId, float fontSize, float x, float y, Vector3 color,
                 std::string content) {
        TextRenderInfo textRenderInfo;
        textRenderInfo.fontId = fontId;
        textRenderInfo.fontSize = fontSize * IMGUI::getBackingRatioY();
        textRenderInfo.x = x;
        textRenderInfo.y = y;
        textRenderInfo.content = content;
        textRenderInfo.color[0] = color.r;
        textRenderInfo.color[1] = color.g;
        textRenderInfo.color[2] = color.b;
        textRenderInfoList.push_back(textRenderInfo);
    }

    void addText(std::string fontName, float fontSize, float x, float y,
                 Vector3 color, std::string content) {
        int fontId = fontList[fontName];
        addText(fontId, fontSize, x, y, color, content);
    }

    void getTextBoundingBox(std::string fontName, float fontSize,
                            std::string content, float* width, float* height) {
        int fontId = fontList[fontName];
        sth_get_text_bounding_box(stash, fontId, fontSize, content.c_str(),
                                  width, height);
        *width = *width * IMGUI::getBackingRatioX();
        *height = *height * IMGUI::getBackingRatioY();
    }

    void render() {
        fontProgram.bind();
        sth_begin_draw(stash);
        for (int i = 0; i < textRenderInfoList.size(); ++i) {
            sth_draw_text(
                stash, textRenderInfoList[i].fontId,
                textRenderInfoList[i].fontSize, textRenderInfoList[i].x,
                textRenderInfoList[i].y, textRenderInfoList[i].color[0],
                textRenderInfoList[i].color[1], textRenderInfoList[i].color[2],
                textRenderInfoList[i].content.c_str(),
                &textRenderInfoList[i].x);
        }
        sth_end_draw(stash);
        textRenderInfoList.clear();
        fontProgram.unbind();
    }

    void flushDraw(sth_texture* texture) {
        int nvert = texture->nverts;
        if (nvert > MAX_VERT_SIZE * 6 / 4)
            nvert = MAX_VERT_SIZE * 6 / 4;
        int vertexIndex = 0;
        int uvIndex = 0;
        int colorIndex = 0;
        for (int i = 0; i < nvert; ++i) {
            vertexBufferData[vertexIndex++] = texture->verts[4 * i];
            vertexBufferData[vertexIndex++] = texture->verts[4 * i + 1];
            uvBufferData[uvIndex++] = texture->verts[4 * i + 2];
            uvBufferData[uvIndex++] = texture->verts[4 * i + 3];
            colorBufferData[colorIndex++] = texture->colors[3 * i];
            colorBufferData[colorIndex++] = texture->colors[3 * i + 1];
            colorBufferData[colorIndex++] = texture->colors[3 * i + 2];
            // convert GL_QAUDS to GL_TRIANGLES
            if (i % 4 == 3) {
                vertexBufferData[vertexIndex++] = texture->verts[4 * (i - 3)];
                vertexBufferData[vertexIndex++] =
                    texture->verts[4 * (i - 3) + 1];
                vertexBufferData[vertexIndex++] = texture->verts[4 * (i - 1)];
                vertexBufferData[vertexIndex++] =
                    texture->verts[4 * (i - 1) + 1];

                uvBufferData[uvIndex++] = texture->verts[4 * (i - 3) + 2];
                uvBufferData[uvIndex++] = texture->verts[4 * (i - 3) + 3];
                uvBufferData[uvIndex++] = texture->verts[4 * (i - 1) + 2];
                uvBufferData[uvIndex++] = texture->verts[4 * (i - 1) + 3];

                colorBufferData[colorIndex++] = texture->colors[3 * (i - 3)];
                colorBufferData[colorIndex++] =
                    texture->colors[3 * (i - 3) + 1];
                colorBufferData[colorIndex++] =
                    texture->colors[3 * (i - 3) + 2];

                colorBufferData[colorIndex++] = texture->colors[3 * (i - 1)];
                colorBufferData[colorIndex++] =
                    texture->colors[3 * (i - 1) + 1];
                colorBufferData[colorIndex++] =
                    texture->colors[3 * (i - 1) + 2];
            }
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = vertexBufferData;
        _VBO.vertexBufferSize = nvert * 6 / 2;
        _VBO.uvBufferData = uvBufferData;
        _VBO.uvBufferSize = nvert * 6 / 2;
        _VBO.colorBufferData = colorBufferData;
        _VBO.colorBufferSize = nvert * 6 / 2 * 3 / 2;
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                   HardwareBuffer::FLAG_UV_BUFFER |
                                   HardwareBuffer::FLAG_COLOR_BUFFER);
        buffer.render(GL_TRIANGLES, 2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLSLShader* getFontShader() {
        return &fontProgram;
    }

    void release() {
        sth_delete(stash);
    }
}
