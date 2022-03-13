#include "camera.hpp"
#include <math.h>

// constructor
camera::camera() {
    position = mVector<double>{std::vector<double>{0.0, -10.0, 0.0}};
    frame = mVector<double>{std::vector<double> {0.0, 0.0, 0.0}}; // looks at origin
    upDir = mVector<double>{std::vector<double> {0.0, 0.0, 1.0}};
    length = 1.0;
    horizontal = 1.0;
    aspectRatio = 1.0;
}

// set camera position
void camera::setPosition(const mVector<double>& newPosition) {
    position = newPosition;
}

// set the frame for the camera to look at
void camera::setFrame(const mVector<double>& newFrame) {
    frame = newFrame;
}

// set vector direction of up
void camera::setUpDirection(const mVector<double>& newUpDir) {
    upDir = newUpDir;
}

// set distance of projection screen from pinhole
void camera::setLength(double newLength) {
    length = newLength;
}

// set horizontal size
void camera::setHorizontal(double newHorz) {
    horizontal = newHorz;
}

// set aspect ratio
void camera::setAspectRatio(double newAspect) {
    aspectRatio = newAspect;
}

// return camera position
mVector<double> camera::getPosition() {
    return position;
}

// return frame
mVector<double> camera::getFrame() {
    return frame;
}

// return up vector
mVector<double> camera::getUpDirection() {
    return upDir;
}

// return distance of projection screen from pinhole
double camera::getLength() {
    return length;
}

// return horizontal size
double camera::getHorizontal() {
    return horizontal;
}

// return aspect ratio
double camera::getAspectRatio() {
    return aspectRatio;
}

// get local horizontal screen coordinate vector
mVector<double> camera::getU() {
    return projectionScreenU;
}

// get local vertical screen coordinate vector
mVector<double> camera::getV() {
    return projectionScreenV;
}

// return vector to center of screen
mVector<double> camera::getScreenCenter() {
    return projectionScreenCenter;
}

// function to calculate camera geometry vectors
void camera::calculateGeometry() {
    // get the vector going from the camera position to where it looks at
    alignmentVector = frame - position;

    // normalize that value, only the direction matters
    alignmentVector.normalize();

    // calculate local screen coordinate vectors U and V, normalize them
    projectionScreenU = mVector<double>::cross(alignmentVector, upDir);
    projectionScreenU.normalize();
    projectionScreenV = mVector<double>::cross(projectionScreenU, alignmentVector);
    projectionScreenV.normalize();

    // find the center of the screen
    projectionScreenCenter = length * alignmentVector + position;

    // set U and V vectors to size and aspect ratio
    projectionScreenU = projectionScreenU * horizontal;
    projectionScreenV = projectionScreenV * (horizontal / aspectRatio);
}

// function to create a light ray
bool camera::createRay(float proScreenX, float proScreenY, ray& cameraRay) {
    // find the 2D screen point (e.g. find the screen pixel)
    mVector<double> screenCoordinate = projectionScreenCenter + (projectionScreenU * proScreenX);
    screenCoordinate = screenCoordinate + (projectionScreenV * proScreenY);
    // use this screen point and the camera position to create the ray
    cameraRay.start = position;
    cameraRay.end = screenCoordinate;
    cameraRay.startToEnd = screenCoordinate - position;
    return true;
}