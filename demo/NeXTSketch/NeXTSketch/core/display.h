#pragma once
#include "line.h"
#include <GL/glut.h>
#include "scene.h"
#include "ray.h"
#include "plane.h"
#include <vector>
void display(void);
extern std::vector<Vector3> pointList;
extern std::vector< std::vector<Vector3> > lineList;
extern plane currPlane;
extern Vector3 currPoint;
