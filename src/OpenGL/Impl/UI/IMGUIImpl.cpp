// Shipeng Xu
// billhsu.x@gmail.com

#include "IMGUIImpl.h"
#include <queue>
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Fonts/FontRenderer.h"

namespace IMGUIImpl {
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    GLSLShader UIProgram;

    float verticesArray[8];
    float uvArray[8];
    float colorArray[16];
    int indices[6];
    float mR = 1, mG = 1, mB = 1, mAlpha = 1;
    void init() {
        uvArray[0] = 0.0f;
        uvArray[1] = 0.0f;
        uvArray[2] = 1.0f;
        uvArray[3] = 0.0f;
        uvArray[4] = 1.0f;
        uvArray[5] = 1.0f;
        uvArray[6] = 0.0f;
        uvArray[7] = 1.0f;

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 0;
        indices[4] = 2;
        indices[5] = 3;

        colorArray[0] = mR;
        colorArray[1] = mG;
        colorArray[2] = mB;
        colorArray[3] = mAlpha;
        colorArray[4] = mR;
        colorArray[5] = mG;
        colorArray[6] = mB;
        colorArray[7] = mAlpha;
        colorArray[8] = mR;
        colorArray[9] = mG;
        colorArray[10] = mB;
        colorArray[11] = mAlpha;
        colorArray[12] = mR;
        colorArray[13] = mG;
        colorArray[14] = mB;
        colorArray[15] = mAlpha;
        VBOInfo.vertexBufferSize = sizeof(verticesArray) / sizeof(float);
        VBOInfo.vertexBufferData = verticesArray;
        VBOInfo.uvBufferSize = sizeof(uvArray) / sizeof(float);
        VBOInfo.uvBufferData = uvArray;
        VBOInfo.colorBufferSize = sizeof(colorArray) / sizeof(float);
        VBOInfo.colorBufferData = colorArray;
        VBOInfo.indexBufferSize = sizeof(indices) / sizeof(int);
        VBOInfo.indexBufferData = indices;
        unsigned int flags = HardwareBuffer::FLAG_VERTEX_BUFFER |
                             HardwareBuffer::FLAG_UV_BUFFER |
                             HardwareBuffer::FLAG_COLOR_BUFFER |
                             HardwareBuffer::FLAG_INDEX_BUFFER;

        buffer.initVBO(VBOInfo, flags);
        buffer.setVBOLocation(HardwareBuffer::FLAG_VERTEX_BUFFER, 0);
        buffer.setVBOLocation(HardwareBuffer::FLAG_UV_BUFFER, 1);
        buffer.setVBOLocation(HardwareBuffer::FLAG_COLOR_BUFFER, 2);

        buffer.setVBOUnitSize(HardwareBuffer::FLAG_VERTEX_BUFFER, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_UV_BUFFER, 2);
        buffer.setVBOUnitSize(HardwareBuffer::FLAG_COLOR_BUFFER, 4);

        UIProgram.loadFromFile(GL_VERTEX_SHADER, "Shader/UI.vs");
        UIProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/UI.fs");
        UIProgram.createProgram();
    }
    void renderRenderItem(RenderItem renderItem) {
        verticesArray[0] = renderItem.vertices[0].x;
        verticesArray[1] = renderItem.vertices[0].y;
        verticesArray[2] = renderItem.vertices[1].x;
        verticesArray[3] = renderItem.vertices[1].y;
        verticesArray[4] = renderItem.vertices[2].x;
        verticesArray[5] = renderItem.vertices[2].y;
        verticesArray[6] = renderItem.vertices[3].x;
        verticesArray[7] = renderItem.vertices[3].y;

        colorArray[0] = renderItem.color.r;
        colorArray[1] = renderItem.color.g;
        colorArray[2] = renderItem.color.b;
        colorArray[3] = renderItem.color.a;
        colorArray[4] = renderItem.color.r;
        colorArray[5] = renderItem.color.g;
        colorArray[6] = renderItem.color.b;
        colorArray[7] = renderItem.color.a;
        colorArray[8] = renderItem.color.r;
        colorArray[9] = renderItem.color.g;
        colorArray[10] = renderItem.color.b;
        colorArray[11] = renderItem.color.a;
        colorArray[12] = renderItem.color.r;
        colorArray[13] = renderItem.color.g;
        colorArray[14] = renderItem.color.b;
        colorArray[15] = renderItem.color.a;

        glActiveTexture(GL_TEXTURE0);
        int texID = TextureManager::getInstance()
                        .getTexture(renderItem.textureFile)
                        .glTextureID;
        if (texID == -1) {
            texID = TextureManager::getInstance().loadTexture(
                renderItem.textureFile, 4);
        }
        glBindTexture(GL_TEXTURE_2D, texID);
        HardwareBuffer::VBOStruct _VBO;
        _VBO.vertexBufferData = verticesArray;
        _VBO.vertexBufferSize = sizeof(verticesArray) / sizeof(float);
        _VBO.colorBufferData = colorArray;
        _VBO.colorBufferSize = sizeof(colorArray) / sizeof(float);
        buffer.updateVBO(_VBO, HardwareBuffer::FLAG_VERTEX_BUFFER |
                                   HardwareBuffer::FLAG_COLOR_BUFFER);
        buffer.render();
        glBindTexture(GL_TEXTURE_2D, 0);
        if (renderItem.type == RENDER_ITEM_LABEL) {
            float fontW = 0, fontH = 0;
            FontRenderer::getTextBoundingBox("WenQuanYiMicroHei", 20,
                                             renderItem.text, &fontW, &fontH);
            float offsetX = (renderItem.size.x - fontW) / 2.f;
            float offsetY = (renderItem.size.y - fontH) / 2.f;
            FontRenderer::addText("WenQuanYiMicroHei", 20,
                                  renderItem.pos.x + offsetX,
                                  renderItem.pos.y + fontH + offsetY,
                                  Vector3(0.1f, 0.1f, 0.1f), renderItem.text);
        }
        if (renderItem.showHintText) {
            float fontW = 0, fontH = 0;
            FontRenderer::getTextBoundingBox("WenQuanYiMicroHei", 20,
                                             renderItem.text, &fontW, &fontH);
            label(getState().mouseX + 10 * IMGUI::getBackingRatioX(),
                  getState().mouseY + 10 * IMGUI::getBackingRatioY(),
                  fontW + 10 * IMGUI::getBackingRatioX(),
                  fontH + 10 * IMGUI::getBackingRatioY(), renderItem.text);
        }
    }
    void render() {
        GLuint local_modelView;
        GLuint local_projection;
        UIProgram.bind();
        local_modelView =
            glGetUniformLocation(UIProgram.getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                           IMGUI::getModelView().get());
        local_projection =
            glGetUniformLocation(UIProgram.getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                           IMGUI::getProjection().get());
        glUniform1i(glGetUniformLocation(UIProgram.getProgram(), "image0"), 0);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        std::queue<RenderItem> renderQueue = getRenderQueue();
        while (renderQueue.size() > 0) {
            RenderItem renderItem = renderQueue.front();
            renderQueue.pop();
            renderRenderItem(renderItem);
        }

        // second pass
        // this is for showing the hint text
        // which is generated in renderRenderItem()
        renderQueue = getRenderQueue();
        while (renderQueue.size() > 0) {
            RenderItem renderItem = renderQueue.front();
            renderQueue.pop();
            renderRenderItem(renderItem);
        }

        // Render Font
        FontRenderer::getFontShader()->bind();
        local_modelView = glGetUniformLocation(
            FontRenderer::getFontShader()->getProgram(), "modelView");
        glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                           IMGUI::getModelView().get());
        local_projection = glGetUniformLocation(
            FontRenderer::getFontShader()->getProgram(), "projection");
        glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                           IMGUI::getProjection().get());
        glUniform1i(glGetUniformLocation(
                        FontRenderer::getFontShader()->getProgram(), "image0"),
                    0);
        FontRenderer::render();

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    }

    GLSLShader& getUIProgram() {
        return UIProgram;
    }
};