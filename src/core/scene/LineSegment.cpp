#include "LineSegment.h"
#include <GL/glut.h>

void LineSegment::render()
{
    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
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
