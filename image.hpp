#ifndef IMAGE_H
#define IMAGE_H

#include <cstring>
#include <vector>
#include <SDL2/SDL.h>

class image {
    public:
        // FUNCTIONS:
        image(); // constructor
        ~image(); // destructor
        // function to initialize the image
        void imageInit(const int xSize, const int ySize, SDL_Renderer *rRenderer);
        // function to set a pixel color on image
        void setPixelColor(const int x, const int y, const double red, const double green, const double blue);
        // function to display the image
        void display();

    private:
        // FUNCTIONS:
        // function to convert RGB values to an integer representation of color space to use with SDL2
        Uint32 convertColor(const double red, const double green, const double blue);
        // function to handle SDL2 texture
        void textureInit();

        // VARIABLES:
        // image dimensions
        int imageX, imageY;
        // color layers for each pixel
        std::vector<std::vector<double>> imageRed;
        std::vector<std::vector<double>> imageGreen;
        std::vector<std::vector<double>> imageBlue;
        // SDL2 rendering + texture
        SDL_Renderer *imageRenderer;
        SDL_Texture *imageTexture;
};

#endif