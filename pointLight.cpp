#include "pointLight.hpp"

// constructor
pointLight::pointLight() {
    lightColor = mVector<double>{std::vector<double> {1.0, 1.0, 1.0}}; // white default color
    lightIntensity = 1.0; // full intensity
    // default location for the light will be at the origin, taken care of already by vector class
}

// destructor
pointLight::~pointLight() {}

// function to compute illumination at angles
bool pointLight::computeIllumination(const mVector<double>& poi, const mVector<double>& localNormal, const std::vector<std::shared_ptr<objectBase>>& objectList, const std::shared_ptr<objectBase>& currentObject, mVector<double>& color, double& intensity) {
    // create a direction vector ppointing from the point of intersection to the light
    mVector<double> lightDir = (lightLocation - poi).getNormalizedCopy();
    // find the angle between the unit vectors of the object local normal and the light direction
    double angle = acos(mVector<double>::dot(localNormal, lightDir));
    // if the normal is pointing away from the light (angle is greater than pi/2) there is no illumination
    if(angle > 1.5708) { // note that 1.5708 is pi/2
        color = lightColor;
        intensity = 0.0; // no illumination;
        return false;
    }
    else {
        color = lightColor;
        // compute the intensity according to the light
        intensity = lightIntensity * (1.0 - (angle / 1.5708));
        return true;
    }
}