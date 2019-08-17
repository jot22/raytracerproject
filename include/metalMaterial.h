//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_METALMATERIAL_H
#define RAYTRACER_METALMATERIAL_H

#include "material.h"

//Creates an approximation for a Metal material.
//The color of the metal can be selected, as well as how "smooth" the metal is, or bumpy.
//"f" value of 0.0 means no fuzziness, 1.0 means the most fuzzy look.
class metalMaterial : public material {
public:
    //Initializes metalMaterial with texture and fuzz
    metalMaterial(texture *a, float f) : albedo(a) {
        if (f < 1) {
            fuzz = f;
        } else {
            fuzz = 1.0f;
        }
    }

    //Destructor for metalMaterial
    ~metalMaterial() {
        delete albedo;
    }

    //Scatters ray for metalMaterial
    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
        attenuation = albedo->value(0, 0, rec.p);
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    //Variables for metalMaterial
    texture *albedo;
    float fuzz;

private:
    //Reflect function for metalMaterial
    vec3 reflect(const vec3 &v, const vec3 &n) const {
        return v - 2 * dot(v, n) * n;
    }

    //random_in_unit_sphere function for metalMaterial
    vec3 random_in_unit_sphere() const {
        vec3 p;
        do {
            p = 2.0f * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) -
                vec3(1, 1, 1);
        } while (p.squared_length() >= 1.0);
        return p;
    }
};

#endif //RAYTRACER_METALMATERIAL_H
