/* 
Shipeng Xu
billhsu.x@gmail.com

Thanks to GLUI2
*/
#pragma once

#include <list>
#include <stddef.h>
#include <GL/freeglut.h>

class UINode
{
public:
    UINode(UINode* parent);
    ~UINode();

    void setPos(int x, int y){mPosX = x; mPosY = y;}
    void getPos(int* x = NULL, int* y = NULL)
    {
        if(x != NULL) *x = mPosX;
        if(y != NULL) *y = mPosY;
    }

    void setSize(int width, int height){mWidth = width; mHeight = height;}
    void getSize(int* width = NULL, int* height = NULL)
    {
        if(width != NULL) *width = mWidth;
        if(height != NULL) *height = mHeight;
    }

    void setColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
    {
        mR = r; mG = g; mB = b; mAlpha = a;
    }
    void getColor(float* r = NULL, float* g = NULL, float* b = NULL, float* a = NULL)
    {
        if(r != NULL)
            *r = mR;
        if(g != NULL)
            *g = mG;
        if(b != NULL)
            *b = mB;
        if(a != NULL)
            *a = mAlpha;
    }
    
    void setVisibility(bool visible){mIsVisible = visible;}
    bool getVisibility(){return mIsVisible;}

    void setDisabled(bool disable){mIsDisabled = disable;}
    bool getDisabled(){return mIsDisabled;}

    void setCallback(void (*callback)(UINode* sender)){mCallBackFunc = callback;}

    virtual void render(float timeDelta){}

    bool insideNode(int x, int y)
    {
        return ((x>=mPosX && x<=mPosX+mWidth)
                &&(y>=mPosY && y<=mPosY+mHeight));
    }
    UINode* getNodeByPos(int x, int y);

    float mR, mG, mB, mAlpha;
    int mPosX, mPosY;
    int mWidth, mHeight;
    enum{NODE_IDLE, NODE_HOVER, NODE_PRESS};
    
    int nodeStatus;

    int nodeID;
    
private:
    bool mIsVisible;
    bool mIsDisabled;
    void (*mCallBackFunc)(UINode* sender);

    std::list< UINode* > mChildNodes;
    typedef std::list< UINode* >::iterator mChildIter;
    typedef std::list< UINode* >::reverse_iterator mChildRevIter;
    
    UINode* mParentNode;

    void _render(float timeDelta);

    friend class UI;
};