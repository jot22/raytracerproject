//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_DIELECTRICMATERIAL_H
#define RAYTRACER_DIELECTRICMATERIAL_H

#include "material.h"

//Creates a di-electric material, basically anything from water, to glass, to an approximation of diamond.
//The type of di-electric material is determined by the refractive index value passed in.
//Glass = ~1.5
//Diamond = ~2.42
class dielectricMaterial : public material {
public:
    //Initializes dielectricMaterial with ref_idx
    explicit dielectricMaterial(float rI) : ref_idx(rI) {}

    //Destructor for dielectricMaterial
    ~dielectricMaterial() {

    }

    //Scatters ray for dielectricMaterial
    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = vec3(1.0, 1.0, 1.0);
        vec3 refracted;

        float reflect_prob;
        float cosine;

        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
            //scattered = ray(rec.p,refracted);
        } else {
            scattered = ray(rec.p, reflected, r_in.time());
            reflect_prob = 1.0f;
        }

        if ((rand() / (RAND_MAX + 1.0)) < reflect_prob) {
            scattered = ray(rec.p, reflected, r_in.time());
        } else {
            scattered = ray(rec.p, refracted, r_in.time());
        }
        return true;
    }

    //Variable for dielectricMaterial
    float ref_idx;
private:
    //What happens if a ray of light reflects off the object.
    vec3 reflect(const vec3 &v, const vec3 &n) const {
        return v - 2 * dot(v, n) * n;
    }

    //What happens if a ray of light refracts off the object.
    bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) const {
        vec3 uv = unit_vector(v);
        float dt = dot(uv, n);
        float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
        if (discriminant > 0) {
            refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        }
        return false;
    }

    //An efficient way of approximating the specular reflection coefficient
    //https://en.wikipedia.org/wiki/Schlick%27s_approximation
    float schlick(float cosine, float ref_idx) const {
        float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
    }
};

#endif //RAYTRACER_DIELECTRICMATERIAL_H
