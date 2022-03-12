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

         // test the camera
         camera testCamera;
         testCamera.setPosition(mVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
         testCamera.setFrame(mVector<double>(std::vector<double>{0.0, 2.0, 0.0}));
         testCamera.setUpDirection(mVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
         testCamera.setLength(1.0);
         testCamera.setHorizontal(1.0);
         testCamera.setAspectRatio(1.0);
         testCamera.calculateGeometry();

         // get the screen center, vectors U and V, and display
         auto screenCenter = testCamera.getScreenCenter();
         auto screenU = testCamera.getU();
         auto screenV = testCamera.getV();

         // display to the terminal
         std::cout << "Camera screen center: " << std::endl;
         printVector(screenCenter);
         std::cout << "\nCamera U vector: " << std::endl;
         printVector(screenU);
         std::cout << "\nCamra V vector: " << std::endl;
         printVector(screenV);
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

        SDL_SetRenderDrawColor(rRenderer, 255, 255, 255, 255); // set the background color to white
        SDL_RenderClear(rRenderer);
        rScene.render(rImage); // render the scene
        rImage.display(); // display the image
        SDL_RenderPresent(rRenderer); // show the result
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