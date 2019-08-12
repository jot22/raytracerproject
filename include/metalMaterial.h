//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_METALMATERIAL_H
#define RAYTRACER_METALMATERIAL_H

#include "material.h"

class metalMaterial : public material {
public:
    metalMaterial(texture *a, float f) : albedo(a) {
        if(f < 1){
            fuzz = f;
        }else{
            fuzz = 1.0f;
        }
    }

    ~metalMaterial(){
        delete[] albedo;
    }

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere(),r_in.time());
        attenuation = albedo->value(0,0,rec.p);
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    texture *albedo;
    float fuzz;

private:
    vec3 reflect(const vec3 &v, const vec3 &n) const {
        return v - 2 * dot(v, n) * n;
    }
    vec3 random_in_unit_sphere() const {
        vec3 p;
        do {
            p = 2.0f * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) - vec3(1, 1, 1);
        } while (p.squared_length() >= 1.0);
        return p;
    }
};

#endif //RAYTRACER_METALMATERIAL_H
