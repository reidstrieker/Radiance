#include "scene.hpp"

// constructor
scene::scene() { }

// function to render image
bool scene::render(image &outputImage) {
    // get dimensions of output image
    int xSize = outputImage.getXSize();
    int ySize = outputImage.getYSize();

    // test code to be deleted later
    // create some color variations
    for(int x = 0; x < xSize; x++) {
        for(int y = 0; y < ySize; y++) {
            double red = (static_cast<double>(x)/static_cast<double>(xSize)) * 255.0;
            double green = (static_cast<double>(y)/static_cast<double>(ySize)) * 255.0;
            outputImage.setPixelColor(x, y, red, green, 0.0);
        }
    }
    return true;
}