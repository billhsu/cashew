/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "Controller.h"
#include "State.h"
#include "../camera/Camera.h"
#include "Scene.h"
#include "../UI/UI.h"
#include "../texture/g2Images.h"

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


void Controller::init()
{
    sidle = new StateIdle();
    sDelLine = new StateDeleteLine();
    sselectPlane = new StateSelectPlane();
    sdraw = new StateDraw();
    camera = &Camera::getInstance();
    
    GUI->resize(originWidth, originHeight);
    int btnSize = 150/2;
    int centerX = width / 2 - btnSize/2;
    int centerY = height - btnSize*2;

    int _w, _h, _ch;
    GLuint TextureID_idle = g2LoadImage("media/textures/button.png", &_w, &_h, &_ch, false, false);
    GLuint TextureID_hover = g2LoadImage("media/textures/button_hover.png", &_w, &_h, &_ch, false, false);
    GLuint TextureID_press = g2LoadImage("media/textures/button_press.png", &_w, &_h, &_ch, false, false);

    btnSelectOneH = GUI->addButton(BTN_ID_SELECT_ONE_H, centerX - btnSize*2, centerY, btnSize, btnSize, 
                        TextureID_idle, TextureID_hover, TextureID_press,
                        "", NULL);
    btnSelectOneH->setColor(1.0f,1.0f,1.0f,0.9f);

    btnSelectOneV = GUI->addButton(BTN_ID_SELECT_ONE, centerX - btnSize*1, centerY, btnSize, btnSize, 
                        TextureID_idle, TextureID_hover, TextureID_press,
                        "", NULL);
    btnSelectOneV->setColor(1.0f,1.0f,1.0f,0.9f);

    btnSelectTwo = GUI->addButton(BTN_ID_SELECT_TWO, centerX, centerY, btnSize, btnSize, 
                        TextureID_idle, TextureID_hover, TextureID_press,
                        "", NULL);
    btnSelectTwo->setColor(1.0f,1.0f,1.0f,0.9f);

    btnSelectTwoV = GUI->addButton(BTN_ID_SELECT_TWO_V, centerX + btnSize*1, centerY, btnSize, btnSize, 
                        TextureID_idle, TextureID_hover, TextureID_press,
                        "", NULL);
    btnSelectTwoV->setColor(1.0f,1.0f,1.0f,0.9f);

    btnSelectThree = GUI->addButton(BTN_ID_SELECT_THREE, centerX + btnSize*2, centerY, btnSize, btnSize, 
                        TextureID_idle, TextureID_hover, TextureID_press,
                        "", NULL);
    btnSelectThree->setColor(1.0f,1.0f,1.0f,0.9f);

    sidle->stateSelectPlane = sselectPlane;
    sidle->stateDeleteLine  = sDelLine;
    sDelLine->stateIdle     = sidle;
    sselectPlane->stateDraw = sdraw;
    sdraw->stateIdle = sidle;
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
        State::currState->UIEvent(node, 1);
    }
    else
    {
        uiHold = 0;
        State::currState->MouseButton(button, state, x, y);
    }

    //std::cout<<"button: "<<button<<" state:"<<state<<std::endl;
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
    GUI->resize(_width, _heigth);
    width = _width;
    height = _heigth;
}