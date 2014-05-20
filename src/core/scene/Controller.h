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

    static std::vector<LineSegment> sketchLines;
    static Plane currPlane; // Plane to draw
    static Vector3 currPoint;
    static bool bCurrPoint;

    int status;

    static int width,height;
    static int mouseX,mouseY;
    static int mouseButton,mouseState; // mouse status
    static int lastMouseX,lastMouseY; // last mouse position


    StateIdle* sidle;
    StateDeleteLine* sDelLine;
    StateSelectPlane* sselectPlane;
    StateDraw* sdraw;
    Camera * camera;
    UI* GUI;
    
    static bool enableLight;
    static Vector3 rotate;

private:
    Controller();
    ~Controller();
    Controller(Controller const&);
    void operator=(Controller const&);
};