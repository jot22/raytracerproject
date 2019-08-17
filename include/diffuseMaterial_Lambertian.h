//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_DIFFUSEMATERIAL_LAMBERTIAN_H
#define RAYTRACER_DIFFUSEMATERIAL_LAMBERTIAN_H

#include "material.h"
#include "texture.h"

//Creates a "matte" style material.
//https://en.wikipedia.org/wiki/Lambertian_reflectance
class diffuseMaterial_Lambertian : public material {
public:
    //Initializes diffuseMaterial_Lambertian with texture
    explicit diffuseMaterial_Lambertian(texture *a) : albedo(a) {}

    //Destructor for diffuseMaterial_Lambertian
    ~diffuseMaterial_Lambertian() {
        delete albedo;
    }

    //Scatters ray for diffuseMaterial_Lambertian
    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

    //Variable for diffuseMaterial_Lambertian
    texture *albedo;

private:
    //Function for random_in_unit_sphere
    vec3 random_in_unit_sphere() const {
        vec3 p;
        do {
            p = 2.0f * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) -
                vec3(1, 1, 1);
        } while (p.squared_length() >= 1.0);
        return p;
    }
};

#endif //RAYTRACER_DIFFUSEMATERIAL_LAMBERTIAN_H
