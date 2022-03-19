#include "lightBase.hpp"

// constructor
lightBase::lightBase() {}

// destructor
lightBase::~lightBase() {}

// function to compute illumination at angles
bool lightBase::computeIllumination(const mVector<double>& poi, const mVector<double>& localNormal, const std::vector<std::shared_ptr<objectBase>>& objectList, const std::shared_ptr<objectBase>& currentObject, mVector<double>& color, double& intensity) {
    return false;
}