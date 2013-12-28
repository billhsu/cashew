#pragma once
#include <iostream>

class Controller
{
public:
    static Controller& getInstance()
    {
        static Controller instance;
        std::cout <<"Controller getInstance()"<<std::endl;
        return instance;
    }
    enum {CTRL_IDLE, CTRL_SELECT_CUR_PLANE, CTRL_DRAW};
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);

private:
    Controller() {};
    Controller(Controller const&);
    void operator=(Controller const&);
};
