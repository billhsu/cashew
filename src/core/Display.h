/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include "Line.h"
#include <GL/glut.h>
#include "Scene.h"
#include "Ray.h"
#include "Plane.h"
#include <vector>
void display(void);
extern std::vector<Vector3> pointList;
extern std::vector< std::vector<Vector3> > lineList;
extern Plane currPlane;
extern Vector3 currPoint;
