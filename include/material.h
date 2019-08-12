//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

struct hit_record;

#include "canHitGeneric.h"


class material  {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
    virtual vec3 emitted(float u, float v, const vec3& p) const{
        return {0,0,0};
    }
};


#endif //RAYTRACER_MATERIAL_H
