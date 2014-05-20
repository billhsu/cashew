/* 
Shipeng Xu
billhsu.x@gmail.com

Thanks to GLUI2
*/
#pragma once

#include <list>

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

    void setSize(int weight, int height){mWeight = weight; mHeight = height;}
    void getSize(int* weight = NULL, int* height = NULL)
    {
        if(weight != NULL) *weight = mWeight;
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

    void setCallback(void (*callback)(UINode* Sender)){mCallback = callback;}

    virtual void render(float timeDelta){}
private:
    float mR, mG, mB, mAlpha;
    int mPosX, mPosY;
    int mWeight, mHeight;

    bool mIsVisible;
    bool mIsDisabled;
    void (*mCallback)(UINode* Sender);

    std::list< UINode* > mChildNodes;
    typedef std::list< UINode* >::iterator mChildIter;
    typedef std::list< UINode* >::reverse_iterator mChildRevIter;
    
    UINode* mParentNode;

    void _render(float timeDelta);

    friend class UI;
};