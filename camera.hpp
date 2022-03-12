#ifndef CAMERA_H
#define CAMERA_H

#include "mVector.hpp"
#include "ray.hpp"

class camera {
    public:
        // FUNCTIONS:
        camera(); // constructor
        void setPosition(const mVector<double>& newPosition); // set camera position
        void setFrame(const mVector<double>& newFrame); // set the frame for the camera to look at
        void setUpDirection(const mVector<double>& newUpDir); // set vector direction of up
        void setLength(double newLength); // set distance of projection screen from pinhole
        void setHorizontal(double newHorz); // set horizontal pixel count
        void setAspectRatio(double newRatio); // set aspect ratio
        mVector<double> getPosition(); // return camera position
        mVector<double> getFrame(); // return frame
        mVector<double> getUpDirection(); // return up vector
        mVector<double> getU(); // get local horizontal screen coordinate vector
        mVector<double> getV(); // get local vertical screen coordinate vector
        mVector<double> getScreenCenter(); // return vector to center of screen
        double getLength(); // return distance of projection screen from pinhole
        double getHorizontal(); // return horizontal pixel count
        double getAspectRatio(); // return aspect ratio
        ray createRay(float proScreenX, float proScreenY); // function to create a light ray
        void calculateGeometry(); // function to calculate camera geometry vectors

    private:
        // VARIABLES:
        mVector<double> position{3}; // camera position
        mVector<double> frame{3}; // direction for camera to look at
        mVector<double> upDir{3}; // up direction vector
        double length; // distance of projection screen from pinhole
        double horizontal; // horizontal screen pixel count
        double aspectRatio; // image aspect ratio
        mVector<double> alignmentVector{3};
        mVector<double> projectionScreenU{3}; // local horizontal screen coordinate vector
        mVector<double> projectionScreenV{3}; // local vertical screen coordinate vector
        mVector<double> projectionScreenCenter{3}; // screen center
};

#endif