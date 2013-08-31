#include "line.h"
#include "glut.h"
void Line::addVec(Vector3 vec)
{
    vectorList.push_back(vec);
}

void Line::render()
{
    for(int i = 0; i < vectorList.size()-1; ++i)
    {
        glBegin(GL_LINES);
        glVertex3fv(vectorList[i].cell);
        glVertex3fv(vectorList[i+1].cell);
        glEnd();
    }
}