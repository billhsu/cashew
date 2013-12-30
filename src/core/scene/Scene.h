/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include "Ray.h"
#include "Plane.h"
#include "Vectors.h"
Vector3 intersect(Ray r, Plane p);
float distRayPoint(Ray r, Vector3 p);
void drawGrid(float size, float step);
void drawAxis(float size);
Ray getMouseRay(int mx, int my); 
bool getRayPoint(Ray selectRay, Vector3& p);
enum {IDLE, SELECT_PLANE, DRAW};
extern int sysMode;
enum {VER_PLANE, HOR_PLANE};
extern int planeMode;
extern bool findCurr;
