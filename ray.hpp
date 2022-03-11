#ifndef RAY_H
#define RAY_H

#include "mVector.hpp"

class ray {
    public:
        // FUNCTIONS:
        // constructor for a ray between two vectors 
        ray(const mVector<double>& startVec, const mVector<double>& endVec);
        // functions to return start and end vectors
        mVector<double> getStart() const;
        mVector<double> getEnd() const;

        // VARIABLES:
        mVector<double> start{3};
        mVector<double> end{3};
        mVector<double> startToEnd{3};
};

#endif