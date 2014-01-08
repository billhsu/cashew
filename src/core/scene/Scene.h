/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include "Ray.h"
#include "Plane.h"
#include "../math/Vectors.h"
Vector3 intersect(Ray r, Plane p);
float distRayPoint(Ray r, Vector3 p);
void drawGrid(float size, float step);
void drawAxis(float size);
