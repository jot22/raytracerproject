//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_CONSTANTTEXTURE_H
#define RAYTRACER_CONSTANTTEXTURE_H

#include "texture.h"

//Creates a texture based on supplied R-G-B values, single color only, stretched across at every point.
class constantTexture : public texture {
public:
    //Default constructor for constantTexture
    constantTexture() = default;

    //Initializes constantTexture with color
    explicit constantTexture(vec3 c) : color(c) {}

    //Destructor for constantTexture
    ~constantTexture() {}

    //Returns color of constantTexture
    vec3 value(float u, float v, const vec3 &p) const override {
        return color;
    }

    //Variable for constantTexture
    vec3 color;
};

#endif //RAYTRACER_CONSTANTTEXTURE_H
