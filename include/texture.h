//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H

#include "vec3.h"

class texture {
public:
    virtual ~texture() {}

    virtual vec3 value(float u, float v, const vec3 &p) const = 0;

};

#endif //RAYTRACER_TEXTURE_H
