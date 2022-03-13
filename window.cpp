#include "window.hpp"
#include "mVector.hpp"

// constructor
window::window() {
    isRunning = true;
    rWindow = NULL;
    rRenderer = NULL;
}

// function to initialize window
bool window::windowInit() { 
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) // initialize SDL2 library
        return false;

    rWindow = SDL_CreateWindow("Radiance", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(rWindow != NULL) { // if we successfully initialized the window
        rRenderer = SDL_CreateRenderer(rWindow, -1, 0);

         // initialize the image instance
         rImage.imageInit(1280, 720, rRenderer);

        // set the background color to white
        SDL_SetRenderDrawColor(rRenderer, 255, 255, 255, 255);
        SDL_RenderClear(rRenderer);
        
        // render the scene
        rScene.render(rImage);

        // display the image
        rImage.display();

        // show the result
        SDL_RenderPresent(rRenderer);
    }
    else
        return false;
    return true;
}

// function to check for events
int window::eventListener() {
    
    SDL_Event event;

    if(windowInit() == false) // if initialization failed
        return -1;

    while(isRunning) { // if the window is running
        while(SDL_PollEvent(&event) != 0) // continuously poll for events
            eventHandler(&event); // handle the event if one is found
    }
    
}

// function to handle events
void window::eventHandler(SDL_Event *event) {
    if(event->type == SDL_QUIT) // if the event signals a quit
        isRunning = false; // set the flag to false to terminate the window
}

// function to handle exiting the window
void window::exit() {
    // exiting SDL2
    SDL_DestroyRenderer(rRenderer);
    SDL_DestroyWindow(rWindow);
    rWindow = NULL;
    SDL_Quit();
}

// function to print vector to terminal
void window::printVector(const mVector<double>& inputVector) {
    int rows = inputVector.getDims();
    for(int row = 0; row < rows; row++)
        std::cout << std::fixed << std::setprecision(3) << inputVector.getElement(row) << std::endl;
}