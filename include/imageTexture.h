//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_IMAGETEXTURE_H
#define RAYTRACER_IMAGETEXTURE_H

#include "texture.h"

//Stretches over a supplied char of pixel data, over a given texture size, A and B (Width and Height).
//Used in our project for loading in a PPM file, and texturing that over a selected object.
//Can also be used for any other type of ingested data, so long as it is converted into a char array of data
class imageTexture : public texture {
public:
    //Default constructor for imageTexture
    imageTexture() {};

    //Initializes imageTexture with ppmLoader, nx, and ny
    imageTexture(ppmLoader *ppm, int A, int B) {
        pixx = ppm;
        pixelData = ppm->getPixelData();
        nx = A;
        ny = B;
    }

    //Destructor for imageTexture
    ~imageTexture() {
        delete pixx;
    }

    //Value for imageTexture
    vec3 value(float u, float v, const vec3 &p) const override;

    //Variables for imageTexture
    ppmLoader *pixx;
    unsigned char *pixelData;
    int nx, ny;
};


//Calculates where each of the ingested array pixel data value goes into the UV coordinate space
vec3 imageTexture::value(float u, float v, const vec3 &p) const {
    auto i = static_cast<int>((u) * nx);
    auto j = static_cast<int>((1 - v) * ny - 0.001);
    if (i < 0) {
        i = 0;
    }
    if (j < 0) {
        j = 0;
    }
    if (i > nx - 1) {
        i = nx - 1;
    }
    if (j > ny - 1) {
        j = ny - 1;
    }

    float r = int(pixelData[3 * i + 3 * nx * j]) / 255.0f;
    float g = int(pixelData[3 * i + 3 * nx * j + 1]) / 255.0f;
    float b = int(pixelData[3 * i + 3 * nx * j + 2]) / 255.0f;
    return {r, g, b};

}

#endif //RAYTRACER_IMAGETEXTURE_H
