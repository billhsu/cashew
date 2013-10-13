#pragma once
#include "ray.h"
#include "plane.h"
#include "vectors.h"
Vector3 intersect(Ray r, plane p);
void drawGrid(float size, float step);
void drawAxis(float size);
Ray getMouseRay(int mx, int my); 
