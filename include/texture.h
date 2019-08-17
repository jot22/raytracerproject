//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H

#include "vec3.h"

//Base class for the concept of a texture, different types of textures can be created, from a simple
//RGB based one, to one loaded from a PPM file.
class texture {
public:
    //destructor for texture
    virtual ~texture() {}

    //returns value for texture
    virtual vec3 value(float u, float v, const vec3 &p) const = 0;

};

#endif //RAYTRACER_TEXTURE_H
