#include "ray.hpp"

ray::ray() {
    start = mVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    end = mVector<double>{std::vector<double>{0.0, 0.0, 1.0}};
    startToEnd = end - start;
}

// constructor for a ray between two vectors
ray::ray(const mVector<double>& startVec, const mVector<double>& endVec) {
    // assign values
    start = startVec;
    end = endVec;
    startToEnd = end - start;
}

// functions to return start and end vectors
mVector<double> ray::getStart() const {
    return start;
}

mVector<double> ray::getEnd() const {
    return end;
}