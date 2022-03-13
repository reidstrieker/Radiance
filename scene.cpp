#include "scene.hpp"

// constructor
scene::scene() {
    // camera configuration
    rCamera.setPosition(mVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    rCamera.setFrame(mVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    rCamera.setUpDirection(mVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    rCamera.setHorizontal(0.25);
    rCamera.setAspectRatio(16.0 / 9.0);
    rCamera.calculateGeometry();
 }

// function to render image
bool scene::render(image &outputImage) {
    // get dimensions of output image
    int xSize = outputImage.getXSize();
    int ySize = outputImage.getYSize();
    // preinstantiate ray
    ray cameraRay;
    mVector<double> poi{3};
    mVector<double> localNormal{3};
    mVector<double> localColor{3};
    // precalculate scaling values
    double xScale = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yScale = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    // loop over every pixel in the image
    for(int y = 0; y < ySize; y++) {
        for(int x = 0; x < xSize; x++) {
            // normalize the x and y coordinates
            double xNorm = (static_cast<double>(x) * xScale) - 1.0;
            double yNorm = (static_cast<double>(y) * yScale) - 1.0;
            // create a ray for this pixel
            rCamera.createRay(xNorm, yNorm, cameraRay);
            // check for an intersection
            if(testSphere.testIntersection(cameraRay, poi, localNormal, localColor)) {
                // change the color of the sphere to red
                outputImage.setPixelColor(x, y, 255.0, 0.0, 0.0);
            }
            else
                // add no color to the image
                outputImage.setPixelColor(x, y, 0.0, 0.0, 0.0);
        }
    }

    return true;
}