#include "image.hpp"

// constructor
image::image() {
    imageX = 0;
    imageY = 0;
    imageRenderer = NULL;
    imageTexture = NULL;
}

// destructor
image::~image() {
    if(imageTexture != NULL)
        SDL_DestroyTexture(imageTexture);
}

// function to initialize the image
void image::imageInit(const int x, const int y, SDL_Renderer *rRenderer) {
    // set correct dimensions for color layers
    imageRed.resize(x, std::vector<double>(y, 0.0));
    imageGreen.resize(x, std::vector<double>(y, 0.0));
    imageBlue.resize(x, std::vector<double>(y, 0.0));

    // set correct image dimensions
    imageX = x;
    imageY = y;

    // store pointer to renderer
    imageRenderer = rRenderer;

    // initialize the texture
    textureInit();
}

// function to set a pixel color on image
void image::setPixelColor(const int x, const int y, const double red, const double green, const double blue) {
    imageRed.at(x).at(y) = red;
    imageGreen.at(x).at(y) = green;
    imageBlue.at(x).at(y) = blue;
}

// function to display the image
void image::display() {
    // allocate memory for a pixel buffer
    Uint32 *tempPixels = new Uint32[imageX * imageY];

    // clear pixel buffer
    memset(tempPixels, 0, imageX * imageY * sizeof(Uint32));

    // calculate and store color values in pixel buffer
    for(int x = 0; x < imageX; x++)
        for(int y = 0; y < imageY; y++)
            tempPixels[x + (y * imageX)] = convertColor(imageRed.at(x).at(y), imageGreen.at(x).at(y), imageBlue.at(x).at(y));

    // update the image texture with the pixel buffer
    SDL_UpdateTexture(imageTexture, NULL, tempPixels, imageX * sizeof(Uint32));
    
    // delete the buffer
    delete[] tempPixels;

    // copy the texture to a rectangular renderer
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = imageX;
    srcRect.h = imageY;
    bounds = srcRect;
    SDL_RenderCopy(imageRenderer, imageTexture, &srcRect, &bounds);
}

// function to handle SDL2 texture
void image::textureInit() {
    // compiler directives to initialize the texture
    Uint32 rmask, gmask, bmask, amask;
	// from SDL2 docs on mask values based on byteorder
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

    // delete any previously created texture
    if(imageTexture != NULL)
        SDL_DestroyTexture(imageTexture);

    // create the texture that will store the image
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, imageX, imageY, 32, rmask, gmask, bmask, amask);
    imageTexture = SDL_CreateTextureFromSurface(imageRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

// function to convert RGB values to an integer representation of color space to use with SDL2
Uint32 image::convertColor(const double red, const double green, const double blue) {
    // convert the colors to unsigned integers
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);

    // compiler directives
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
	#endif

	return pixelColor;
}

// functions to return image dimensions
int image::getXSize() {
    return imageX;
}

int image::getYSize() {
    return imageY;
}