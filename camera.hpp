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
        mVector<double> getScreenCenter();
        double getLength();
        double getHorizontal();
        double getAspectRatio();
        ray createRay(float proScreenX, float proScreenY);
        void updateCameraGeometry();

    private:
        // VARIABLES:
        mVector<double> position{3};
        mVector<double> frame{3};
        mVector<double> upDir{3};
        double length;
        double horizontal;
        double aspectRatio;
        mVector<double> alignmentVector{3};
        mVector<double> projectionScreenU{3};
        mVector<double> projectionScreenV{3};
        mVector<double> projectionScreenCenter{3};
};

#endif