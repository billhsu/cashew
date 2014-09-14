/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "Controller.h"
#include "State.h"
#include "StateIdle.h"
#include "StateDeleteLine.h"
#include "StateSelectPlane.h"
#include "StateDraw.h"
#include "Camera.h"
#include "Scene.h"
#include "UI.h"
#include "g2Images.h"
#include "luatables.h"
#include "luaUtility.h"

State* State::currState;

int Controller::width = 800;
int Controller::height = 600;
int Controller::originWidth = 800;
int Controller::originHeight = 600;
int Controller::mouseX = 0;
int Controller::mouseY = 0;
int Controller::mouseButton;
int Controller::mouseState;
int Controller::lastMouseX = 0;
int Controller::lastMouseY = 0;

int Controller::uiHold = 0;

LuaTable *Controller::UILayout = NULL;

UIButton *Controller::btnSelectVerticalPlane  = NULL, *Controller::btnSelectHorizontalPlane = NULL;
UIButton *Controller::btnConfirmPlane  = NULL, *Controller::btnCancelPlane = NULL;
UIButton *Controller::btnDrawPlaneDone = NULL;
UIButton *Controller::btnUndo = NULL;
UIButton *Controller::btnDeleteLine = NULL, *Controller::btnStandardView = NULL;
UIButton *Controller::btnDocNew  = NULL, *Controller::btnDocOpen = NULL,
         *Controller::btnDocSave = NULL;
UIButton *Controller::btnDeleteLineDone = NULL;
UIButton *Controller::btnMirror = NULL;

UILabel  *Controller::lbFPS = NULL;

UIRadioButton *Controller::rbtnSelect = NULL;

Plane Controller::currPlane = Plane();
bool Controller::enableLight = false;

std::vector<LineSegment> Controller::sketchLines;

Vector3 Controller::currPoint = Vector3(0,0,0);
bool Controller::bCurrPoint = false;

Vector3 Controller::rotate = Vector3(-30,0,0);

UI* Controller::GUI = &UI::getInstance();

lua_State *Controller::luaState = NULL;

Controller::Controller()
{
    std::cout <<"Controller Controller()"<<std::endl;
}

Controller::~Controller()
{
    delete sIdle;
    delete sSelectPlane;
    delete sDraw;
    delete sDelLine;
    lua_close(luaState);
    std::cout <<"Controller ~Controller()"<<std::endl;
}

void Controller::UIButtonCallback(UINode* sender)
{
    std::cout<<"UIButtonCallback"<<std::endl;
    if(sender->nodeID == BTN_ID_DOC_NEW)
    {
        sketchLines.clear();
    }
    else State::currState->UIEvent(sender, EVENT_BTN_CLICKED);
}

int Controller::getNodePosX(const char *nodeName)
{
    std::cout<<nodeName<<std::endl;
    std::string stringValue = (*UILayout)[nodeName]["pos"]["x"].get<std::string> ();
    std::cout<<"stringValue "<<stringValue<<std::endl;
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int Controller::getNodePosY(const char *nodeName)
{
    std::cout<<nodeName<<std::endl;
    std::string stringValue = (*UILayout)[nodeName]["pos"]["y"].get<std::string> ();
    std::cout<<"stringValue "<<stringValue<<std::endl;
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int Controller::getNodeWidth(const char *nodeName)
{
    std::cout<<nodeName<<std::endl;
    std::string stringValue = (*UILayout)[nodeName]["size"]["width"].get<std::string> ();
    std::cout<<"stringValue "<<stringValue<<std::endl;
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int Controller::getNodeHeight(const char *nodeName)
{
    std::cout<<nodeName<<std::endl;
    std::string stringValue = (*UILayout)[nodeName]["size"]["height"].get<std::string> ();
    std::cout<<"stringValue "<<stringValue<<std::endl;
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}
void Controller::init()
{
    luaState = luaL_newstate();
    luaL_openlibs( luaState );

    // Load the program
    UILayout = LuaTable::fromFile("UILayout.lua");
    std::cout<<getNodePosX("BTN_ID_DOC_NEW")<<std::endl;
    std::cout<<getNodePosX("BTN_ID_DOC_NEW")<<std::endl;

    for(int i=0; i < State::STATE_ID_MAX; ++i)
    {
        State::statePool[i] = NULL;
    }
    sIdle = new StateIdle();
    sDelLine = new StateDeleteLine();
    sSelectPlane = new StateSelectPlane();
    sDraw = new StateDraw();
    camera = &Camera::getInstance();
    
    GUI->resize(originWidth, originHeight);
    
    int btnSize = 80/2;
    int centerX = width / 2 - btnSize/2;
    int centerY = 0 + btnSize * 2;

    int _w, _h, _ch;

    GLuint TextureID_new  = g2LoadImage("media/textures/button_document_new.png", &_w, &_h, &_ch, false, true);
    GLuint TextureID_open = g2LoadImage("media/textures/button_document_open.png", &_w, &_h, &_ch, false, true);
    GLuint TextureID_save = g2LoadImage("media/textures/button_document_save.png", &_w, &_h, &_ch, false, true);

    GLuint TextureID_select_vertical = g2LoadImage("media/textures/button_vertical.png", &_w, &_h, &_ch, false, true);
    GLuint TextureID_select_horizontal = g2LoadImage("media/textures/button_horizontal.png", &_w, &_h, &_ch, false, true);

    GLuint TextureID_confirm = g2LoadImage("media/textures/button_confirm.png", &_w, &_h, &_ch, false, true);
    GLuint TextureID_cancel  = g2LoadImage("media/textures/button_cancel.png",  &_w, &_h, &_ch, false, true);

    GLuint TextureID_standardView = g2LoadImage("media/textures/button_standard_view.png", &_w, &_h, &_ch, false, true);
    GLuint TextureID_deleteLine   = g2LoadImage("media/textures/button_delete.png"       , &_w, &_h, &_ch, false, true);
    GLuint TextureID_undo         = g2LoadImage("media/textures/button_undo.png"         , &_w, &_h, &_ch, false, true);

    GLuint TextureID_mirror       = g2LoadImage("media/textures/button_mirror.png"         , &_w, &_h, &_ch, false, true);

    btnDocNew = GUI->addButton(BTN_ID_DOC_NEW, "BTN_ID_DOC_NEW", 
                        TextureID_new, TextureID_new, TextureID_new, "New Sketch", Controller::UIButtonCallback, NULL);
    btnDocOpen = GUI->addButton(BTN_ID_DOC_OPEN, width - btnSize*1, centerY - btnSize*0, btnSize, btnSize, 
                        TextureID_open, TextureID_open, TextureID_open, "Open", Controller::UIButtonCallback, NULL);
    btnDocSave = GUI->addButton(BTN_ID_DOC_SAVE, width - btnSize*1, centerY + btnSize*1.2, btnSize, btnSize, 
                        TextureID_save, TextureID_save, TextureID_save, "Save", Controller::UIButtonCallback, NULL);

    btnSize = 120/2;
    centerX = width / 2 - btnSize/2;
    centerY = height - 2 * btnSize;

    btnSelectVerticalPlane = GUI->addButton(BTN_ID_SELECT_VERTICAL, centerX - btnSize*1, centerY, btnSize, btnSize, 
                                    TextureID_select_vertical, TextureID_select_vertical, TextureID_select_vertical, "Change plane direction", Controller::UIButtonCallback, NULL);
    btnSelectVerticalPlane->setVisibility(false);

    btnSelectHorizontalPlane = GUI->addButton(BTN_ID_SELECT_HORIZONTAL, centerX + btnSize*1, centerY, btnSize, btnSize, 
                                    TextureID_select_horizontal, TextureID_select_horizontal, TextureID_select_horizontal, "Change plane direction", Controller::UIButtonCallback, NULL);
    btnSelectHorizontalPlane->setVisibility(false);

    btnSize = 120/2;
    centerX = 0 + btnSize/2;
    centerY = height - 2 * btnSize;
    btnConfirmPlane = GUI->addButton(BTN_ID_CONFIRM_PLANE, centerX, centerY, btnSize, btnSize, 
                                    TextureID_confirm, TextureID_confirm, TextureID_confirm, "Confirm", Controller::UIButtonCallback, NULL);
    btnConfirmPlane->setVisibility(false);

    btnCancelPlane  = GUI->addButton(BTN_ID_CANCEL_PLANE, centerX + btnSize*1.2, centerY, btnSize, btnSize, 
                                    TextureID_cancel, TextureID_cancel, TextureID_cancel, "Cancel", Controller::UIButtonCallback, NULL);
    btnCancelPlane->setVisibility(false);

    centerX = width - btnSize/2;
    btnDrawPlaneDone = GUI->addButton(BTN_ID_DRAW_PLANE_DONE, centerX, centerY, btnSize, btnSize, 
                                    TextureID_confirm, TextureID_confirm, TextureID_confirm, "Done", Controller::UIButtonCallback, NULL);
    btnDrawPlaneDone->setVisibility(false);

    btnDeleteLineDone = GUI->addButton(BTN_ID_DELETE_LINE_DONE, centerX, centerY, btnSize, btnSize, 
                                    TextureID_confirm, TextureID_confirm, TextureID_confirm, "Done", Controller::UIButtonCallback, NULL);
    btnDeleteLineDone->setVisibility(false);

    centerX = width / 2;
    centerY = btnSize / 2;
    btnStandardView = GUI->addButton(BTN_ID_STANDARD_VIEW, centerX - btnSize * 1.2 * 2, centerY, btnSize, btnSize, 
                                    TextureID_standardView, TextureID_standardView, TextureID_standardView, "Standard View", Controller::UIButtonCallback, NULL);
    btnStandardView->setVisibility(false);

    btnUndo = GUI->addButton(BTN_ID_UNDO, centerX - btnSize, centerY, btnSize, btnSize, 
                                    TextureID_undo, TextureID_undo, TextureID_undo, "Undo", Controller::UIButtonCallback, NULL);
    btnUndo->setVisibility(false);

    btnDeleteLine   = GUI->addButton(BTN_ID_DELETE_LINE, centerX + btnSize * 0, centerY, btnSize, btnSize, 
                                    TextureID_deleteLine, TextureID_deleteLine, TextureID_deleteLine, "Delete lines", Controller::UIButtonCallback, NULL);
    btnDeleteLine->setVisibility(false);

    btnMirror   = GUI->addButton(BTN_ID_MIRROR, centerX + btnSize * 1.2, centerY, btnSize, btnSize, 
                                    TextureID_mirror, TextureID_mirror, TextureID_mirror, "Mirror Mode", Controller::UIButtonCallback, NULL);
    btnMirror->setVisibility(false);

    lbFPS = GUI->addLabel(LBL_FPS, 0, 20, 20, 40, "");
    lbFPS->setColor(0.5f,0.5f,0.5f,0.9f);

    State::enterState(sIdle);

}
void Controller::MouseButton(int button, int state, int x, int y)
{
    Controller::mouseButton = button;
    Controller::mouseState = state;
    Controller::mouseX = x;
    Controller::mouseY = y;
    UINode* node = GUI->MouseButton(button, state, x, y);
    if(node!=NULL)
    {
        uiHold = 1;
    }
    else
    {
        uiHold = 0;
        State::currState->MouseButton(button, state, x, y);
    }
}

void Controller::MouseMotion(int x, int y)
{
    Controller::mouseX = x;
    Controller::mouseY = y;
    if(uiHold==0) State::currState->MouseMotion(x, y);
}
void Controller::PassiveMotion(int x, int y)
{
    Controller::mouseX = x;
    Controller::mouseY = y;
    Vector3 p;
    
    GUI->PassiveMotion(x, y);

    if(camera->getPoint(p))
    {
        currPoint = p;
        bCurrPoint = true;
    }
    else bCurrPoint = false;
    if(uiHold==0) State::currState->PassiveMotion(x, y);
}
void Controller::Keyboard(unsigned char key, int x, int y)
{
    Controller::mouseX = x;
    Controller::mouseY = y;

    if(key == 27) exit(1);
    else if(key == 'r') 
    {
        if(sketchLines.size()>0)
            sketchLines.pop_back();
    }
    else
        State::currState->Keyboard(key, x, y);
}

void Controller::render(float timeDelta)
{
    glClearColor (0.9f, 0.9f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera->update(timeDelta);

    drawGrid(20.0f,1.0f);
    drawAxis(2.0f);

    for(int i=0; i<sketchLines.size(); ++i)
    {
        sketchLines[i].render();
    }

    State::currState->render(timeDelta);
    
    if(bCurrPoint)
    {
        glDisable(GL_DEPTH);
        glPointSize(5);
        glBegin(GL_POINTS);
        glColor3f(1,0,0);
            glVertex3fv(currPoint.cell);
        glEnd();
        glPointSize(1);
        glEnable(GL_DEPTH);
    }

    GUI->render(timeDelta);
    
    glutPostRedisplay();
    glutSwapBuffers();
}

void Controller::resize(int _width, int _heigth)
{
    width = _width;
    height = _heigth;

    lua_pushnumber(UILayout->L, width);
    lua_setglobal(UILayout->L, "window_width");
    lua_pushnumber(UILayout->L, height);
    lua_setglobal(UILayout->L, "window_height");

    GUI->resize(width, height);

    int btnSize = 80/2;
    int centerX = width / 2 - btnSize/2;
    int centerY = 0 + btnSize * 2;

    btnDocNew->setPos(width - btnSize*1, centerY - btnSize*1.2);
    btnDocOpen->setPos(width - btnSize*1, centerY - btnSize*0);
    btnDocSave->setPos(width - btnSize*1, centerY + btnSize*1.2);

    btnSize = 120/2;
    centerX = width / 2 - btnSize/2;
    centerY = height - 2 * btnSize;

    btnSelectVerticalPlane->setPos(centerX - btnSize*1, centerY);
    btnSelectHorizontalPlane->setPos(centerX + btnSize*1, centerY);

    btnSize = 120/2;
    centerX = 0 + btnSize/2;
    centerY = height - 2 * btnSize;

    btnConfirmPlane->setPos(centerX, centerY);
    btnCancelPlane->setPos(centerX + btnSize*1.2, centerY);

    centerX = width - btnSize;
    btnDrawPlaneDone->setPos(centerX, centerY);
    btnDeleteLineDone->setPos(centerX, centerY);

    centerX = width / 2;
    centerY = btnSize / 2;
    btnStandardView->setPos(centerX - btnSize * 1.2 * 2, centerY);
    btnUndo->setPos(centerX - btnSize * 1.2, centerY);
    btnDeleteLine->setPos(centerX + btnSize * 0, centerY);
    btnMirror->setPos(centerX + btnSize * 1.2, centerY);
}
