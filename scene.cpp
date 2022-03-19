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
    // create a sphere instance and construct a shared pointer to that
    objectList.push_back(std::make_shared<sphere> (sphere()));
    // create a light instance and construct a shared pointer to that
    lightList.push_back(std::make_shared<pointLight> (pointLight()));
    lightList[0]->lightLocation = mVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
    lightList[0]->lightColor = mVector<double> {std::vector<double> {255.0, 255.0, 255.0}};
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
            // check for intersections with all objects in the scene
            for(auto currentObject : objectList) {
                // if there is an intersection
                if(currentObject->testIntersection(cameraRay, poi, localNormal, localColor)) {
                    // compute intensity of illumination
                    double intensity;
                    mVector<double> color{3};
                    bool validIllum = false;
                    for(auto currentLight : lightList) {
                        validIllum = currentLight->computeIllumination(poi, localNormal, objectList, currentObject, color, intensity);
                    }
                    // compute distance between camera and point of intersection
                    double dist = (poi - cameraRay.start).getNorm(); // recall this calculates vector length
                    // set min and max distances accordingly
                    if(dist > maxDist)
                        maxDist = dist;
                    if(dist < minDist)
                        minDist = dist;
                    // change the color of the sphere according to light illumination
                    if(validIllum) {
                        outputImage.setPixelColor(x, y, 255.0 * intensity, 0.0, 0.0);
                    }
                    else {
                        outputImage.setPixelColor(x, y, 0.0, 0.0, 0.0);
                    }
                }
                else {
                    // add no color to the image
                    outputImage.setPixelColor(x, y, 0.0, 0.0, 0.0);
                }
            }
        }
    }
    std::cout << "minDist: " << minDist << std::endl;
    std::cout << "maxDist: " << maxDist << std::endl;
    return true;
}