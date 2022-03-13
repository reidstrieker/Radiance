#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "mVector.hpp"
#include "ray.hpp"

class objectBase {
    public:
        // FUNCTIONS:
        // constructor
        objectBase();
        // destructor, virtual so it must be overridden
        virtual ~objectBase();
        // function to test whether a casted ray has a point of intersection with the object
        virtual bool testIntersection(const ray& castRay, mVector<double>& poi, mVector<double>& localNormal, mVector<double>& localColor);
        // function to test whether two floating-point numbers are close to being equal
        bool closeEnough(const double f1, const double f2);

        // VARIABLES:
        // base color of the object
        mVector<double> baseColor{3};
};

#endif