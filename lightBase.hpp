#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "mVector.hpp"
#include "ray.hpp"
#include "objectBase.hpp"

class lightBase {
    public:
        // FUNCTIONS:
        // constructor
        lightBase();
        // destructor to be overridden
        virtual ~lightBase(); // destructor
        // function to compute illumination at angles
        virtual bool computeIllumination(const mVector<double>& poi, const mVector<double>& localNormal, const std::vector<std::shared_ptr<objectBase>>& objectList, const std::shared_ptr<objectBase>& currentObject, mVector<double>& color, double& intensity);

        // VARIABLES:
        mVector<double> lightColor{3};
        mVector<double> lightLocation{3};
        double lightIntensity;
};


#endif