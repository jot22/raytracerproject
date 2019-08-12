//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_CONSTANTTEXTURE_H
#define RAYTRACER_CONSTANTTEXTURE_H

#include "texture.h"

class constantTexture : public texture {
public:
    constantTexture() = default;

    ~constantTexture() {}

    explicit constantTexture(vec3 c) : color(c) {}

    vec3 value(float u, float v, const vec3 &p) const override {
        return color;
    }

    vec3 color;
};

#endif //RAYTRACER_CONSTANTTEXTURE_H
