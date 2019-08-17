//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_CHECKERBOARDTEXTURE_H
#define RAYTRACER_CHECKERBOARDTEXTURE_H

#include "texture.h"

//Creates a checkerboard pattern texture that can be applied to any Material class
class checkerBoardTexture : public texture {
public:
    //Default constructor for checkBoardTexture
    checkerBoardTexture() = default;

    //Initializes checkerBoardTexture with input textures
    checkerBoardTexture(texture *t0, texture *t1) {
        odd = t1;
        even = t0;
    }

    //Destructor for checkerBoardTexture
    ~checkerBoardTexture() {
        delete odd;
        delete even;
    }

    //Calculates which square of the checkerboard should be which color, two colors are supported
    vec3 value(float u, float v, const vec3 &p) const override {
        float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sines < 0) {
            return odd->value(u, v, p);
        }
        return even->value(u, v, p);
    }

    //Variables for checkerBoardTexture
    texture *odd;
    texture *even;
};

#endif //RAYTRACER_CHECKERBOARDTEXTURE_H
