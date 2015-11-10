// Shipeng Xu
// billhsu.x@gmail.com

#include "LineSegment.h"
#include <stdlib.h>
#define SMALL_NUM 0.001f

float LineSegment::distSegmentSegment(LineSegment S1, LineSegment S2) {
    Vector3 u = S1.points[1] - S1.points[0];
    Vector3 v = S2.points[1] - S2.points[0];
    Vector3 w = S1.points[0] - S2.points[0];
    float a = u.dot(u);  // always >= 0
    float b = u.dot(v);
    float c = v.dot(v);  // always >= 0
    float d = u.dot(w);
    float e = v.dot(w);
    float D = a * c - b * b;  // always >= 0
    float sc, sN, sD = D;     // sc = sN / sD, default sD = D >= 0
    float tc, tN, tD = D;     // tc = tN / tD, default tD = D >= 0

    // compute the line parameters of the two closest points
    if (D < SMALL_NUM) {  // the lines are almost parallel
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    } else {  // get the closest points on the infinite lines
        sN = (b * e - c * d);
        tN = (a * e - b * d);
        if (sN < 0.0) {  // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        } else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {  // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    } else if (tN > tD) {  // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d + b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (std::abs(sN) < SMALL_NUM ? 0.0 : sN / sD);
    tc = (std::abs(tN) < SMALL_NUM ? 0.0 : tN / tD);

    // get the difference of the two closest points
    Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

    return dP.length();  // return the closest distance
}