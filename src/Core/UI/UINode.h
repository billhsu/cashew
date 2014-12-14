/*
 Shipeng Xu
 billhsu.x@gmail.com
 
 Thanks to GLUI2
 */
#pragma once

#include <list>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

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
    
    // timeMs = 120 works prefect
    void appearIn(float timeMs = 120.0f);
    void appearOut(float timeMs = 120.0f);
    
    void setCallback(void (*callback)(UINode* sender)){mCallBackFunc = callback;}
    void update(float timeDelta);
    virtual void render(){}
    
    bool insideNode(int x, int y)
    {
        if(!getVisibility()) return false;
        return ((x>=mPosX && x<mPosX+mWidth)
                &&(y>=mPosY && y<mPosY+mHeight));
    }
    UINode* getNodeByPos(int x, int y);
    
    virtual void MouseButton(int button, int state, int x, int y){};
    virtual void PassiveMotion(int x, int y){};
    
    enum{NODE_IDLE, NODE_HOVER, NODE_PRESS};
    
    int nodeStatus;
    
    int nodeID;
    
    char strID[128];
    
protected:
    float mR, mG, mB, mAlpha;
    int mPosX, mPosY;
    int mWidth, mHeight;
    char mText[512];
    
    UINode* previousPressed;
    UINode* previousHover;
    
    long timeMsAniStart, timeMsTotalForAni; // for animation
    bool isAnimation;
    enum{UI_ANIM_IN, UI_ANIM_OUT};
    int aniStatus;
    
    float mTimeAccu; // total time after changing to current state
    
    bool mIsVisible;
    bool mIsDisabled;
    void (*mCallBackFunc)(UINode* sender);
    
    UINode* mParentNode;
    
private:
    std::list< UINode* > mChildNodes;
    typedef std::list< UINode* >::iterator mChildIter;
    typedef std::list< UINode* >::reverse_iterator mChildRevIter;

    friend class UI;
};