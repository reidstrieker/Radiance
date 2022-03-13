#include "objectBase.hpp"
#include <math.h>

// used for function closeEnough
#define EPSILON 1e-21f;

// constructor
objectBase::objectBase() {

}

// destructor, will be overridden
objectBase::~objectBase() {

}

// function to test whether a casted ray has a point of intersection with the object
bool objectBase::testIntersection(const ray& castRay, mVector<double>& poi, mVector<double>& localNormal, mVector<double>& localColor) {
    // this will be overridden by object subclasses
    return false;
}

// function to test whether two floating-point numbers are close to being equal
bool objectBase::closeEnough(const double f1, const double f2) {
    // return whether the difference between f1 and f2 is less than our pre-defined epsilon
    return fabs(f1 - f2) < EPSILON;
}