#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.H"
#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"

class window {
    public:
        // FUNCTIONS:
        window(); // constructor
        bool windowInit(); // function to initialize window
        int eventListener(); // function to check for events
        void eventHandler(SDL_Event *event); // function to handle events
        void exit(); // function to handle exiting the window

    private:
        // FUNCTIONS:
        void printVector(const mVector<double>& inputVector); // function to print vector to terminal

        // VARIABLES:
        image rImage; // variable to store the image
        scene rScene; // instance of the scene class
        bool isRunning; // flag to tell if window is running 
        SDL_Window *rWindow; // pointer to the SDL window
        SDL_Renderer *rRenderer; // pointer to the SDL renderer
};

#endif