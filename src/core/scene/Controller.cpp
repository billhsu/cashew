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

UIButton *Controller::btnSelectVerticalPlane  = NULL, *Controller::btnSelectHorizontalPlane = NULL;
UIButton *Controller::btnConfirmPlane  = NULL, *Controller::btnCancelPlane = NULL;
UIButton *Controller::btnDrawPlaneDone = NULL;

UIButton *Controller::btnDocNew  = NULL, *Controller::btnDocOpen = NULL,
         *Controller::btnDocSave = NULL;

UILabel  *Controller::lbFPS = NULL;

UIRadioButton *Controller::rbtnSelect = NULL;

Plane Controller::currPlane = Plane();
bool Controller::enableLight = false;

std::vector<LineSegment> Controller::sketchLines;

Vector3 Controller::currPoint = Vector3(0,0,0);
bool Controller::bCurrPoint = false;

Vector3 Controller::rotate = Vector3(-30,0,0);

UI* Controller::GUI = &UI::getInstance();

Controller::Controller()
{
    std::cout <<"Controller Controller()"<<std::endl;
}

Controller::~Controller()
{
    delete sidle;
    delete sselectPlane;
    delete sdraw;
    delete sDelLine;

    std::cout <<"Controller ~Controller()"<<std::endl;
}

void Controller::UIButtonCallback(UINode* sender)
{
    std::cout<<"UIButtonCallback"<<std::endl;
    State::currState->UIEvent(sender, EVENT_BTN_CLICKED);
}

void Controller::init()
{
    for(int i=0; i < State::STATE_ID_MAX; ++i)
    {
        State::statePool[i] = NULL;
    }
    sidle = new StateIdle();
    sDelLine = new StateDeleteLine();
    sselectPlane = new StateSelectPlane();
    sdraw = new StateDraw();
    camera = &Camera::getInstance();
    
    GUI->resize(originWidth, originHeight);
    
    int btnSize = 120/2;
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

    btnDocNew = GUI->addButton(BTN_ID_DOC_NEW, width - btnSize*1, centerY - btnSize*1.2, btnSize, btnSize, 
                        TextureID_new, TextureID_new, TextureID_new, "", Controller::UIButtonCallback, NULL);
    btnDocOpen = GUI->addButton(BTN_ID_DOC_OPEN, width - btnSize*1, centerY - btnSize*0, btnSize, btnSize, 
                        TextureID_open, TextureID_open, TextureID_open, "", Controller::UIButtonCallback, NULL);
    btnDocSave = GUI->addButton(BTN_ID_DOC_SAVE, width - btnSize*1, centerY + btnSize*1.2, btnSize, btnSize, 
                        TextureID_save, TextureID_save, TextureID_save, "", Controller::UIButtonCallback, NULL);

    btnSize = 120/2;
    centerX = width / 2 - btnSize/2;
    centerY = height - 2 * btnSize;

    btnSelectVerticalPlane = GUI->addButton(BTN_ID_SELECT_VERTICAL, centerX - btnSize*1, centerY, btnSize, btnSize, 
                                    TextureID_select_vertical, TextureID_select_vertical, TextureID_select_vertical, "", Controller::UIButtonCallback, NULL);
    btnSelectVerticalPlane->setVisibility(false);

    btnSelectHorizontalPlane = GUI->addButton(BTN_ID_SELECT_HORIZONTAL, centerX + btnSize*1, centerY, btnSize, btnSize, 
                                    TextureID_select_horizontal, TextureID_select_horizontal, TextureID_select_horizontal, "", Controller::UIButtonCallback, NULL);
    btnSelectHorizontalPlane->setVisibility(false);

    btnSize = 120/2;
    centerX = 0 + btnSize/2;
    centerY = height - 2 * btnSize;
    btnConfirmPlane = GUI->addButton(BTN_ID_CONFIRM_PLANE, centerX, centerY, btnSize, btnSize, 
                                    TextureID_confirm, TextureID_confirm, TextureID_confirm, "", Controller::UIButtonCallback, NULL);
    btnConfirmPlane->setVisibility(false);

    btnCancelPlane  = GUI->addButton(BTN_ID_CANCEL_PLANE, centerX + btnSize*1.2, centerY, btnSize, btnSize, 
                                    TextureID_cancel, TextureID_cancel, TextureID_cancel, "", Controller::UIButtonCallback, NULL);
    btnCancelPlane->setVisibility(false);

    centerX = width - btnSize/2;
    btnDrawPlaneDone = GUI->addButton(BTN_ID_DRAW_PLANE_DONE, centerX, centerY, btnSize, btnSize, 
                                    TextureID_confirm, TextureID_confirm, TextureID_confirm, "", Controller::UIButtonCallback, NULL);
    btnDrawPlaneDone->setVisibility(false);

    lbFPS = GUI->addLabel(LBL_FPS, 0, 20, 20, 40, "");
    lbFPS->setColor(0.5f,0.5f,0.5f,0.9f);

    State::enterState(sidle);

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

    GUI->resize(width, height);

    int btnSize = 120/2;
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
}
