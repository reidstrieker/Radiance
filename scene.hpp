#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "mVector.hpp"
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "pointLight.hpp"

class scene {
    public:
        // FUNCTIONS:
        scene(); // constructor
        bool render(image &outputImage); // function to render image

    private:
        // VARIABLES:
        camera rCamera; // camera instance
        std::vector<std::shared_ptr<objectBase>> objectList; // list of objects in the scene
        std::vector<std::shared_ptr<lightBase>> lightList; // list of light sources in the scene
};

#endif