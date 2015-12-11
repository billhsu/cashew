//
//  CashewApp.m
//  cashew
//
//  Created by Xu, Shipeng on 23/11/14.
//  Copyright (c) 2014 Xu, Shipeng. All rights reserved.
//

#import <OpenGL/gl3.h>
#import "CashewOpenGLView.h"
#import "CashewInputController.h"
#include "Core/Math/Vectors.h"
#include "Core/Math/Matrices.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include "Core/Controller/MouseEventQueue.h"
#include "Core/Basic/SketchLine.h"

#include "Core/Camera/Camera.h"
#include "OpenGL/Impl/State/StateIdleImpl.h"
#include "OpenGL/Impl/State/StateMoveCenterImpl.h"
#include "OpenGL/Impl/State/StateSelectPlaneImpl.h"
#include "OpenGL/Impl/State/StateDrawImpl.h"
#include "OpenGL/Impl/State/StateDeleteImpl.h"
#include "OpenGL/Impl/State/StateMirrorImpl.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Impl/UI/IMGUIImpl.h"
#include "OpenGL/Util/Utility.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/Impl/Basic/PlaneRenderer.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"

#include "OpenGL/Fonts/FontRenderer.h"

#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "Core/Controller/Mouse.h"
#include "FileOperations.h"
#include "FileOperationsCppWrapper.h"
#include <fstream>
#include <sstream>
#include <queue>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

DepthPeeling* depthPeeling;
TextureManager* textureManager;

Controller* mController = &Controller::getInstance();
FileOperations* fileOperations = [FileOperations alloc];
bool windowPaused = false;

#define BACKGROUND_COLOR 0.2f, 0.2f, 0.2f, 1

@interface CashewApp : NSObject<CashewOpenGLViewDelegate, CashewInputDelegate>

@end

@implementation CashewApp

- (BOOL)prepareRenderData {
    [[CashewInputController sharedInputController] addEventDelegate:self];
    NSLog(@"prepareRenderData");

    textureManager = &TextureManager::getInstance();
    textureManager->loadTexture("media/textures/point_selected.png", 4);
    textureManager->loadTexture("media/textures/point_current.png", 4);
    textureManager->loadTexture("media/textures/button_cancel.png", 4);
    textureManager->loadTexture("media/textures/button_confirm.png", 4);
    textureManager->loadTexture("media/textures/button_movecenter.png", 4);
    textureManager->loadTexture("media/textures/button_horizontal.png", 4);
    textureManager->loadTexture("media/textures/button_vertical.png", 4);
    textureManager->loadTexture("media/textures/social-icon.png", 4);
    textureManager->loadTexture("media/textures/point_3.png", 4);
    textureManager->loadTexture("media/textures/point_4.png", 4);
    textureManager->loadTexture("media/textures/FFFFFF-1.png", 4);

    Scene::prepareSceneAxis(1.0f);
    Scene::prepareSceneGrid(20.0f, 1.0f);

    for (int i = 0; i < State::STATE_ID_MAX; ++i) {
        State::statePool[i] = NULL;
    }
    mController->init();
    mController->state_idle = new StateIdleImpl();
    mController->state_move_center = new StateMoveCenterImpl();
    mController->state_select_plane = new StateSelectPlaneImpl();
    mController->state_draw = new StateDrawImpl();
    mController->state_delete = new StateDeleteImpl();
    mController->state_mirror = new StateMirrorImpl();

    lua_register(Controller::luaState, "newFile", newFile);
    lua_register(Controller::luaState, "saveFile", saveFile);
    lua_register(Controller::luaState, "openFile", openFile);

    State::enterState(mController->state_idle);

    PlaneRenderer::prepareRenderData();
    PointRenderer::prepareRenderData();
    LineSegmentRenderer::prepareRenderData();
    FontRenderer::prepareRenderData();
    IMGUIImpl::prepareRenderData();

    depthPeeling = &DepthPeeling::getInstance();
    depthPeeling->setPassCount(2);
    depthPeeling->setWindowSize(mController->windowWidth,
                                mController->windowHeight);
    depthPeeling->init();
    depthPeeling->setBackgroundColor(BACKGROUND_COLOR);

    MouseEventQueue::init();

    return YES;
}

int newFile(lua_State* L) {
    std::string option =
        showNewFileDialogWrapper((__bridge void*)fileOperations);
    if (option == "OK") {
        SketchLine::getGlobalSketchLines().clear();
    }
    return 0;
}

std::string vectorsToSTLFacet(Vector3 v1, Vector3 v2, Vector3 v3) {
    std::ostringstream buffer;
    buffer << "  facet normal 0 0 0" << std::endl;
    buffer << "    outer loop" << std::endl;
    buffer << "      vertex " << v1.x << " " << v1.z << " " << v1.y
           << std::endl;
    buffer << "      vertex " << v2.x << " " << v2.z << " " << v2.y
           << std::endl;
    buffer << "      vertex " << v3.x << " " << v3.z << " " << v3.y
           << std::endl;
    buffer << "    endloop" << std::endl;
    buffer << "  endfacet" << std::endl;
    return buffer.str();
}

std::string lineSegmentToSTLCube(LineSegment line) {
    std::ostringstream buffer;
    Vector3 vectors[8];
    float scale = 0.3f;

    Vector3 xBase = Vector3(1, 0, 0).cross(line.points[0] - line.points[1]);
    Vector3 yBase = Vector3(0, 1, 0).cross(line.points[0] - line.points[1]);
    Vector3 zBase = Vector3(0, 0, 1).cross(line.points[0] - line.points[1]);
    Vector3 hBase, vBase;
    if (xBase.length() <= yBase.length() && xBase.length() <= zBase.length()) {
        hBase = yBase.normalize() * scale;
        vBase = zBase.normalize() * scale;
    } else if (yBase.length() <= xBase.length() &&
               yBase.length() <= zBase.length()) {
        hBase = xBase.normalize() * scale;
        vBase = zBase.normalize() * scale;
    } else if (zBase.length() <= xBase.length() &&
               zBase.length() <= yBase.length()) {
        hBase = xBase.normalize() * scale;
        vBase = yBase.normalize() * scale;
    }
    vectors[0] = line.points[0] + hBase;
    vectors[1] = line.points[0] + vBase;
    vectors[2] = line.points[0] - hBase;
    vectors[3] = line.points[0] - vBase;

    vectors[4] = line.points[1] + hBase;
    vectors[5] = line.points[1] + vBase;
    vectors[6] = line.points[1] - hBase;
    vectors[7] = line.points[1] - vBase;
    // up
    buffer << vectorsToSTLFacet(vectors[0], vectors[1], vectors[2]);
    buffer << vectorsToSTLFacet(vectors[2], vectors[3], vectors[0]);
    // bottom
    buffer << vectorsToSTLFacet(vectors[4], vectors[5], vectors[6]);
    buffer << vectorsToSTLFacet(vectors[6], vectors[7], vectors[4]);
    // front
    buffer << vectorsToSTLFacet(vectors[0], vectors[1], vectors[5]);
    buffer << vectorsToSTLFacet(vectors[5], vectors[4], vectors[0]);
    // back
    buffer << vectorsToSTLFacet(vectors[2], vectors[3], vectors[7]);
    buffer << vectorsToSTLFacet(vectors[7], vectors[6], vectors[2]);
    // left
    buffer << vectorsToSTLFacet(vectors[0], vectors[3], vectors[7]);
    buffer << vectorsToSTLFacet(vectors[7], vectors[4], vectors[0]);
    // right
    buffer << vectorsToSTLFacet(vectors[1], vectors[2], vectors[6]);
    buffer << vectorsToSTLFacet(vectors[6], vectors[5], vectors[1]);

    return buffer.str();
}

int saveFile(lua_State* L) {
    windowPaused = true;
    std::string filename =
        showSaveFileDialogWrapper((__bridge void*)fileOperations);
    windowPaused = false;
    if (filename == "")
        return 0;
    std::cout << "Saving to " << filename << std::endl;
    std::ofstream fileStream;
    fileStream.open(filename);
    //    if (filename.substr(filename.find_last_of(".") + 1) == "cashew") {
    //        fileStream << "cashew_v1" << std::endl;
    //        fileStream << Controller::sketchLines.size() << std::endl;
    //        for (int i = 0; i < Controller::sketchLines.size(); ++i) {
    //            fileStream << Controller::sketchLines[i].points[0] << " "
    //                       << Controller::sketchLines[i].points[1] <<
    //                       std::endl;
    //        }
    //    } else if (filename.substr(filename.find_last_of(".") + 1) == "stl") {
    //        fileStream << "solid cashew" << std::endl;
    //        for (int i = 0; i < Controller::sketchLines.size(); ++i) {
    //            fileStream << lineSegmentToSTLCube(Controller::sketchLines[i])
    //                       << std::endl;
    //        }
    //        fileStream << "endsolid cashew" << std::endl;
    //    }
    fileStream.close();
    MouseEventQueue::clear();
    return 0;
}

int openFile(lua_State* L) {
    windowPaused = true;
    std::string filename =
        showOpenFileDialogWrapper((__bridge void*)fileOperations);
    windowPaused = false;
    //    if (filename == "")
    //        return 0;
    //    std::cout << "Opening " << filename << std::endl;
    //    Controller::sketchLines.clear();
    //    std::ifstream fileStream;
    //    fileStream.open(filename);
    //    std::string versionStr;
    //    fileStream >> versionStr;
    //    std::cout << "Cashew version: " << versionStr << std::endl;
    //    int sketchSize;
    //    fileStream >> sketchSize;
    //    std::cout << "Sketches: " << sketchSize << std::endl;
    //    for (int i = 0; i < sketchSize; ++i) {
    //        Vector3 point1, point2;
    //        fileStream >> point1 >> point2;
    //        LineSegment line = LineSegment(point1, point2);
    //        Controller::addLine(line);
    //    }
    //    Controller::lineOperations.clear();
    //    Controller::redoOperations.clear();
    //    Controller::deletedLines.clear();
    //    Controller::redoLines.clear();
    //    fileStream.close();
    MouseEventQueue::clear();
    return 0;
}

- (void)mouseLeftUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;

    MouseEvent event;
    event.mouseButton = Mouse::MOUSE_BUTTON_LEFT;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_UP;
    event.mousePosX = x;
    event.mousePosY = y;

    MouseEventQueue::addEvent(event);
}

- (void)mouseLeftDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;

    MouseEvent event;
    event.mouseButton = Mouse::MOUSE_BUTTON_LEFT;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_DOWN;
    event.mousePosX = x;
    event.mousePosY = y;

    MouseEventQueue::addEvent(event);
}

- (void)mouseRightUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;

    MouseEvent event;
    event.mouseButton = Mouse::MOUSE_BUTTON_RIGHT;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_UP;
    event.mousePosX = x;
    event.mousePosY = y;

    MouseEventQueue::addEvent(event);
}

- (void)mouseRightDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;

    MouseEvent event;
    event.mouseButton = Mouse::MOUSE_BUTTON_RIGHT;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_DOWN;
    event.mousePosX = x;
    event.mousePosY = y;

    MouseEventQueue::addEvent(event);
}

- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y {
    y = mController->windowHeight - y;

    MouseEvent event;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_MOTION;
    event.mousePosX = x;
    event.mousePosY = y;

    MouseEventQueue::addEvent(event);
}
- (void)mouseRightDragWithDX:(CGFloat)dx
                       andDY:(CGFloat)dy
                        andX:(CGFloat)x
                        andY:(CGFloat)y {
    y = mController->windowHeight - y;

    MouseEvent event;
    event.mouseButton = Mouse::MOUSE_BUTTON_RIGHT;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_DRAG;
    event.mousePosX = x;
    event.mousePosY = y;
    event.mouseDragX = dx;
    event.mouseDragY = dy;
    MouseEventQueue::addEvent(event);
}

- (void)mouseLeftDragWithDX:(CGFloat)dx
                      andDY:(CGFloat)dy
                       andX:(CGFloat)x
                       andY:(CGFloat)y {
    y = mController->windowHeight - y;
    MouseEvent event;
    event.mouseButton = Mouse::MOUSE_BUTTON_LEFT;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_DRAG;
    event.mousePosX = x;
    event.mousePosY = y;
    event.mouseDragX = dx;
    event.mouseDragY = dy;
    MouseEventQueue::addEvent(event);
}

- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y {
    MouseEvent event;
    event.mouseButtonAction = Mouse::MOUSE_ACTION_SCROLL;
    event.mouseButton = Mouse::MOUSE_BUTTON_SCROLL;
    event.mouseScroll = y;
    MouseEventQueue::addEvent(event);
}
- (void)mouseEnteredWithX:(CGFloat)x andY:(CGFloat)y {
    windowPaused = false;
}
- (void)mouseExitedWithX:(CGFloat)x andY:(CGFloat)y {
    windowPaused = true;
    if (State::currState->getStateID() == State::STATE_DRAW) {
        if (StateDraw::internalState ==
            StateDraw::STATE_DRAW_START_POINT_SELECTED) {
            windowPaused = false;
        }
    }
}
- (void)keyDown:(unichar)key {
    mController->Keyboard(key, Controller::KEY_DOWN);
}
- (void)keyUp:(unichar)key {
    mController->Keyboard(key, Controller::KEY_UP);
}
- (void)update:(NSTimeInterval)timeInterval {
    if (windowPaused) {
        return;
    }
    int numClickEvents = 0;
    std::queue<MouseEvent> queueCpy = MouseEventQueue::getQueueCpy();
    while (queueCpy.size() > 0) {
        MouseEvent event = queueCpy.front();
        if (event.mouseButtonAction == Mouse::MOUSE_ACTION_DOWN ||
            event.mouseButtonAction == Mouse::MOUSE_ACTION_UP) {
            ++numClickEvents;
        }
        processMouseEventForUI(event);
        queueCpy.pop();
        if (numClickEvents >= 1) {
            break;
        }
    }
    MouseEvent event;
    while (MouseEventQueue::pollEvent(event)) {
        processMouseEvent(event);
    }
    IMGUIImpl::beginFrame();
    mController->update(timeInterval * 1000.0f);
    IMGUIImpl::endFrame();
}

void processMouseEventForUI(MouseEvent event) {
    IMGUI::getState().setMouseButton(event.mouseButton);
    IMGUI::getState().setMouseState(event.mouseButtonAction);
    IMGUI::getState().setMousePos(event.mousePosX, event.mousePosY);
}
void processMouseEvent(MouseEvent event) {
    switch (event.mouseButtonAction) {
        case Mouse::MOUSE_ACTION_UP:
        case Mouse::MOUSE_ACTION_DOWN:
            mController->MouseButton(event.mouseButton, event.mouseButtonAction,
                                     event.mousePosX, event.mousePosY);
            break;
        case Mouse::MOUSE_ACTION_MOTION:
            mController->PassiveMotion(event.mousePosX, event.mousePosY);
            break;
        case Mouse::MOUSE_ACTION_DRAG:
            if (event.mouseButton == Mouse::MOUSE_BUTTON_RIGHT) {
                mController->MouseRightDrag(event.mousePosX, event.mousePosY,
                                            event.mouseDragX, event.mouseDragY);
            } else if (event.mouseButton == Mouse::MOUSE_BUTTON_LEFT) {
                mController->MouseLeftDrag(event.mousePosX, event.mousePosY,
                                           event.mouseDragX, event.mouseDragY);
            }
            break;
        case Mouse::MOUSE_ACTION_SCROLL:
            mController->MouseButton(event.mouseButton, (int)event.mouseScroll,
                                     mController->mouseX, mController->mouseY);
            break;
        default:
            break;
    }
}

- (void)render;
{
    if (windowPaused)
        return;
    glViewport(0, 0, mController->windowWidth, mController->windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BACKGROUND_COLOR);
    mController->render();
    depthPeeling->render();
    IMGUIImpl::render();
#ifdef DEBUG
    checkGlErr(__FILE__, __LINE__);
#endif
}
- (void)reshapeRect:(NSRect)rect backing:(NSRect)backing {
    windowPaused = false;
    IMGUI::setBackingRatio(backing.size.width / rect.size.width,
                           backing.size.height / rect.size.height);
    mController->resize(backing.size.width, backing.size.height);
    depthPeeling->setWindowSize(backing.size.width, backing.size.height);
}

- (void)reshapeWidth:(int)width height:(int)height {
    windowPaused = false;
    mController->resize(width, height);
    depthPeeling->setWindowSize(width, height);
}
@end

@implementation CashewOpenGLView (CashewMain)

- (void)prepareOpenGL {
    NSLog(@"prepareOpenGL");
    [super prepareOpenGL];
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(BACKGROUND_COLOR);
    NSString* resourcePath = [[NSBundle mainBundle] resourcePath];
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:resourcePath];
    NSLog(@"%@", resourcePath);

    GLint range[2];
    glGetIntegerv(GL_ALIASED_LINE_WIDTH_RANGE, range);
    glGetIntegerv(GL_SMOOTH_LINE_WIDTH_RANGE, range);
    Set_OpenGLViewDelegate(CashewApp);
}

- (void)clearGLContext {
    NSLog(@"clearGLContext");
    Scene::clearScene();
    PointRenderer::release();
    LineSegmentRenderer::release();
    FontRenderer::release();
    [super clearGLContext];
}

@end
