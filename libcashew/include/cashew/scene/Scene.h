/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include "cashew/scene/Ray.h"
#include "cashew/scene/Plane.h"
#include "cashew/math/Vectors.h"
#include "cashew/scene/LineSegment.h"
Vector3 intersect(Ray r, Plane p);
float distRayPoint(Ray r, Vector3 p);
float distSegmentSegment( LineSegment S1, LineSegment S2);
void drawGrid(float size, float step);
void drawAxis(float size);
