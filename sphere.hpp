#ifndef SPHERE_H
#define SPHERE_H

#include "objectBase.hpp"

class sphere : public objectBase {
    public:
        // FUNCTIONS:
        // constructor (defines a unit sphere at the origin)
        sphere();
        // destructor (objectBase override)
        virtual ~sphere() override;
        // function to test whether a casted ray has a point of intersection with the object (objectBase override)
        virtual bool testIntersection(const ray& castRay, mVector<double>& poi, mVector<double>& localNormal, mVector<double>& localColor);
};

#endif