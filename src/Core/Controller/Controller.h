/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <iostream>
#include <vector>
#include "Core/Math/Vectors.h"
#include "Core/Basic/Plane.h"
#include "Core/Basic/Ray.h"
#include "Core/Basic/LineSegment.h"
#include "Core/Math/Matrices.h"

class State;
class Camera;
class UI;
class UINode;
class UIButton;
class UILabel;
class UIRadioButton;
class lua_State;
class Texture;
class UI;
class UINode;
class UIButton;
class UILabel;

class Controller
{
public:
    static Controller& getInstance()
    {
        static Controller instance;
        std::cout <<"Controller getInstance()"<<std::endl;
        return instance;
    }

    void MouseButton(int button, int state, int x, int y);
    void MouseLeftDrag(int dx, int dy);
    void MouseRightDrag(int dx, int dy);
    void PassiveMotion(int x, int y);
    enum {KEY_UP, KEY_DOWN};
    void Keyboard(unsigned char key, unsigned char status);
    void update(float timeDelta);
    void render();
    
    void init();

    void resize(int _width, int _heigth);
    static void UIButtonCallback(UINode* sender);

    enum {OPERATION_ADD_LINE = 1, OPERATION_DELETE_LINE};
    struct LineOperation
    {
        int lineID;
        int operation;
    };

    static std::vector<LineSegment> sketchLines;
    static std::vector<LineSegment> deletedLines;
    static std::vector<LineOperation> lineOperations;
    static void addLine(LineSegment l)
    {
        static int IDCounter = 0;
        l.ID = IDCounter++;
        LineOperation lineOp;
        lineOp.lineID = l.ID;
        lineOp.operation = OPERATION_ADD_LINE;
        lineOperations.push_back(lineOp);
        sketchLines.push_back(l);
    }
    static void delLine(LineSegment& l)
    {
        for(int i = 0; i < sketchLines.size(); ++i)
        {
            if(sketchLines[i].ID == l.ID)
            {
                LineOperation lineOp;
                lineOp.lineID = l.ID;
                lineOp.operation = OPERATION_DELETE_LINE;
                lineOperations.push_back(lineOp);
                deletedLines.push_back(sketchLines[i]);
                sketchLines.erase(Controller::sketchLines.begin()+i);
                break;
            }
        }
    }

    static Plane currPlane; // Plane to draw
    static Vector3 currPoint;
    static bool bCurrPoint;

    int status;

    static int windowWidth,windowHeight;
    static Matrix4 modelView;
    static Matrix4 projection;
    static int originWidth,originHeight;
    static int mouseX,mouseY;
    static int mouseButton,mouseState; // mouse status

    static UI* GUI;
    static int uiHold;

    static State* state_idle;
    static State* state_select_plane;
    static State* state_draw;
    
    Camera * camera;
    bool getCameraPoint(Vector3& p, const Plane& plane, bool mode);
    Ray getCameraRay();
    static bool enableLight;
    static Vector3 rotate;
    static lua_State *luaState;
    
    static UIButton *btnDocNew, *btnDocOpen, *btnDocSave;

private:
    Controller();
    ~Controller();
    Controller(Controller const&);
    void operator=(Controller const&);
};
