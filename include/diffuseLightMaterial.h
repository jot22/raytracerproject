//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_DIFFUSELIGHTMATERIAL_H
#define RAYTRACER_DIFFUSELIGHTMATERIAL_H

#include "material.h"
#include "texture.h"

//Creates a material that emits light, rather than absorbing it.
//Useful for creating a point of light, a lamp, a ceiling light, etc
class diffuseLightMaterial : public material {
public:
    diffuseLightMaterial() {}

    diffuseLightMaterial(texture *a) {
        emit = a;
    }

    ~diffuseLightMaterial() {
        delete emit;
    }

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        return false;
    }

    vec3 emitted(float u, float v, const vec3 &p) const override {
        return emit->value(u, v, p);
    }

    texture *emit;

};

#endif //RAYTRACER_DIFFUSELIGHTMATERIAL_H
