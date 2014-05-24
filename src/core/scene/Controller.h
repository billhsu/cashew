/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <iostream>
#include <vector>
#include "../math/Vectors.h"
#include "Plane.h"
#include "LineSegment.h"
#include <GL/freeglut.h>

class StateIdle;
class StateDraw;
class StateSelectPlane;
class StateDeleteLine;
class State;
class Camera;
class UI;
class UIButton;

class Controller
{
public:
    static Controller& getInstance()
    {
        static Controller instance;
        std::cout <<"Controller getInstance()"<<std::endl;
        return instance;
    }

    
    void init();
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);
    void render(float timeDelta);

    static void resize(int _width, int _heigth);

    static std::vector<LineSegment> sketchLines;
    static Plane currPlane; // Plane to draw
    static Vector3 currPoint;
    static bool bCurrPoint;

    int status;

    static int width,height;
    static int originWidth,originHeight;
    static int mouseX,mouseY;
    static int mouseButton,mouseState; // mouse status
    static int lastMouseX,lastMouseY; // last mouse position

    static int uiHold;


    StateIdle* sidle;
    StateDeleteLine* sDelLine;
    StateSelectPlane* sselectPlane;
    StateDraw* sdraw;
    Camera * camera;

    static UI* GUI;
    UIButton *btnSelectOneH, *btnSelectOneV, *btnSelectTwo, 
             *btnSelectTwoV, *btnSelectThree;

    static bool enableLight;
    static Vector3 rotate;

private:
    Controller();
    ~Controller();
    Controller(Controller const&);
    void operator=(Controller const&);
};