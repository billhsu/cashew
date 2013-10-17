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
