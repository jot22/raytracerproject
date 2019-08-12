//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_SPHERECANHIT_H
#define RAYTRACER_SPHERECANHIT_H

#include "canHitGeneric.h"

class sphereCanHit : public canHitGeneric {
public:
    sphereCanHit() = default;

    sphereCanHit(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};


    bool hit(const ray &r, float tMin, float tMax, hit_record &rec) const override;

    bool bounding_box(float t0, float t1, aabb &box) const override;

    vec3 center;
    float radius{};
    material *mat_ptr{};
};

bool sphereCanHit::bounding_box(float t0, float t1, aabb &box) const {
    box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
    return true;
}

bool sphereCanHit::hit(const ray &r, float tMin, float tMax, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin) {
            rec.t = temp;
            rec.p = r.point_at_param(rec.t);
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin) {
            rec.t = temp;
            rec.p = r.point_at_param(rec.t);
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}


#endif //RAYTRACER_SPHERECANHIT_H
