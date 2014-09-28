#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>

#ifdef __APPLE__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


unsigned long getMicroSec();
unsigned long getMilliSec();
bool floatEq(float a, float b);
float deg2rad(float deg);
float rad2deg(float rad);

const int FPS_LOCK = 60; // lock FPS to 60.
const float FPS_INTERVAL_MS = 1000.0f/FPS_LOCK;
const float PI = 3.14159265f;
