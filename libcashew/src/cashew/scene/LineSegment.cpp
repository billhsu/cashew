#include "LineSegment.h"
#include "impl/glut.h"

void LineSegment::render(float r, float g, float b)
{
    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3f(r, g, b);
    glVertex3fv(points[0].cell);
    glVertex3fv(points[1].cell);
    glEnd();
    glPointSize(4);
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    glVertex3fv(points[0].cell);
    glVertex3fv(points[1].cell);
    glEnd();
    glPointSize(1);
    glLineWidth(1);
}