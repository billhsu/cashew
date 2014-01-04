#include "LineSegment.h"
#include <GL/glut.h>

void LineSegment::render()
{
    glBegin(GL_LINES);
    glVertex3fv(points[0].cell);
    glVertex3fv(points[1].cell);
    glEnd();
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex3fv(points[0].cell);
    glVertex3fv(points[1].cell);
    glEnd();
    glPointSize(1);
}
