#include "sphere.hpp"
#include <cmath>

// constructor (defines a unit sphere at the origin)
sphere::sphere() {

}

// destructor (objectBase override)
sphere::~sphere() {

}

// function to test whether a casted ray has a point of intersection with the object (objectBase override)
bool sphere::testIntersection(const ray& castRay, mVector<double>& poi, mVector<double>& localNormal, mVector<double>& localColor) {
    // view ray_sphere_intersection.gif for more detail
    // we set the ray equation equal to the sphere equation 
    // and solve for t to find points of intersection
    // this equation reduces to:
    // t^2(v)^2 + 2t((p_0-O)*v) + (p_0-O)^2 - r^2 = 0
    // note that we defined spheres at a local origin so O = 0
    // as such, we can calculate ray-sphere intersections with the quadratic formula
    // a = v^2, direction of castRay is a unit vector so a = 1 always
    // b = 2v*p_0, where v is direction of castRay and p_0 is the start of castRay
    // c = (p_0)^2-r^2, where r is the radius of the sphere
    // and we can test if there is an intersection by checking if this is true:
    // b^2-4ac > 0

    mVector<double> rayDir = castRay.startToEnd; // get direction of ray
    rayDir.normalize(); // make sure direction is a unit vector
    mVector<double> rayStart = castRay.getStart(); // get start of ray
    double a = 1.0; // this is not needed
    double b = 2.0 * mVector<double>::dot(rayDir, rayStart);
    double c = mVector<double>::dot(rayStart, rayStart) - 1.0; // we subtract 1 as this is a unit sphere and r = 1
    if(((b*b)-(4.0*c)) > 0.0)
        return true;
    return false;
}