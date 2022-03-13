#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "mVector.hpp"
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "sphere.hpp"

class scene {
    public:
        // FUNCTIONS:
        scene(); // constructor
        bool render(image &outputImage); // function to render image

    private:
        // VARIABLES:
        camera rCamera; // camera instance
        sphere testSphere; // test sphere
};

#endif