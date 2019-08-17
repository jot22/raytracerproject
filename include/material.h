//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

struct hit_record;

#include "canHitGeneric.h"

//Base class for which every canHitGeneric objects intakes. This is the "skin" of every canHitGeneric object.
//Can be anything from a Metal, to Glass, to a PPM loaded Texture.
class material {
public:

    //Destructor for material
    virtual ~material() {}

    //Scatters ray for material
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;

    //By default, no Material emits any light
    virtual vec3 emitted(float u, float v, const vec3 &p) const {
        return {0, 0, 0};
    }
};


#endif //RAYTRACER_MATERIAL_H
