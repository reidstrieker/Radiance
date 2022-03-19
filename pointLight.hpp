#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightBase.hpp"

class pointLight : public lightBase { // inherits from lightBase
    public:
        // FUNCTIONS:
        // constructor
        pointLight();
        // destructor, overriding lightBase
        virtual ~pointLight() override;
        // function to compute illumination at angles, overriding lightBase
        virtual bool computeIllumination(const mVector<double>& poi, const mVector<double>& localNormal, const std::vector<std::shared_ptr<objectBase>>& objectList, const std::shared_ptr<objectBase>& currentObject, mVector<double>& color, double& intensity) override;
};

#endif