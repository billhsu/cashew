#pragma once
#include "ray.h"
#include "plane.h"
#include "vectors.h"
Vector3 intersect(Ray r, plane p);
float distRayPoint(Ray r, Vector3 p);
void drawGrid(float size, float step);
void drawAxis(float size);
void drawPlane(Vector3 center, plane p, float size);
Ray getMouseRay(int mx, int my); 
bool getRayPoint(Ray selectRay, Vector3& p);
enum {IDLE, DRAW};
extern int sysMode;
enum {VER_PLANE, HOR_PLANE};
extern int planeMode;
extern bool findCurr;
