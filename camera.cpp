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

void camera::setPosition(const mVector<double>& newPosition) {
    position = newPosition;
}

void camera::setFrame(const mVector<double>& newFrame) {
    frame = newFrame;
}

void camera::setUpDirection(const mVector<double>& newUpDir) {
    upDir = newUpDir;
}

void camera::setLength(double newLength) {
    length = newLength;
}

void camera::setHorizontal(double newHorz) {
    horizontal = newHorz;
}

void camera::setAspectRatio(double newAspect) {
    aspectRatio = newAspect;
}

mVector<double> camera::getPosition() {
    return position;
}

mVector<double> camera::getFrame() {
    return frame;
}

mVector<double> camera::getUpDirection() {
    return upDir;
}

double camera::getLength() {
    return length;
}

double camera::getHorizontal() {
    return horizontal;
}

double camera::getAspectRatio() {
    return aspectRatio;
}

mVector<double> camera::getU() {
    return projectionScreenU;
}

mVector<double> camera::getV() {
    return projectionScreenV;
}

mVector<double> camera::getScreenCenter() {
    return projectionScreenCenter;
}

void camera::updateCameraGeometry() {
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

ray camera::createRay(float proScreenX, float proScreenY) {
    // find the 2D screen point (e.g. find the screen pixel)
    mVector<double> screenCoordinate = projectionScreenCenter + (projectionScreenU * proScreenX) + (projectionScreenV * proScreenY);
    return ray(position, screenCoordinate);
}