/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <iostream>
#include <vector>
#include "Vectors.h"
#include "Plane.h"
#include <GL/glut.h>

class StateIdle;
class StateDraw;
class StateSelectPlane;
class State;

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



    std::vector<Vector3> highlightedPoints;
    Plane currPlane; // Plane to draw

    int status;

    int width,height;
    int mouseX,mouseY;
    int mouseButton,mouseState; // mouse status
    int lastMouseX,lastMouseY; // last mouse position


    StateIdle* sidle;
    StateSelectPlane* sselectPlane;
    StateDraw* sdraw;

private:
    Controller();
    ~Controller();
    Controller(Controller const&);
    void operator=(Controller const&);
};
