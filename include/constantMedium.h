//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_CONSTANTMEDIUM_H
#define RAYTRACER_CONSTANTMEDIUM_H

#include <cfloat>
#include "canHitGeneric.h"
#include "texture.h"
#include "isotrophic.h"

class constantMedium : public canHitGeneric {
public:
    constantMedium(canHitGeneric *b, float d, texture *a) {
        boundary = b;
        density = d;
        phaseFunc = new isotrophic(a);
    }

    ~constantMedium() {
        delete phaseFunc;
    }

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    bool bounding_box(float t0, float t1, aabb &box) const override {
        return boundary->bounding_box(t0, t1, box);
    }

    canHitGeneric *boundary;
    float density;
    material *phaseFunc;
};

#endif //RAYTRACER_CONSTANTMEDIUM_H

bool constantMedium::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    bool db = ((rand() / (RAND_MAX + 1.0)) < 0.00001);
    db = false;
    hit_record rec1, rec2;
    if (boundary->hit(r, -FLT_MAX, FLT_MAX, rec1)) {
        if (boundary->hit(r, rec1.t + 0.0001, FLT_MAX, rec2)) {
            if (db) {

            }
            if (rec1.t < t_min) {
                rec1.t = t_min;
            }
            if (rec2.t > t_max) {
                rec2.t = t_max;
            }
            if (rec1.t >= rec2.t) {
                return false;
            }
            if (rec1.t < 0) {
                rec.t = 0;
            }
            float dist_in_bound = (rec2.t - rec1.t) * r.direction().length();
            float hitDist = -(1.0f / density) * log((rand() / (RAND_MAX + 1.0)));
            if (hitDist < dist_in_bound) {
                if (db) std::cerr << "\n";
                rec.t = rec1.t + hitDist / r.direction().length();
                rec.p = r.point_at_param(rec.t);
                rec.normal = vec3(1, 0, 0);
                rec.mat_ptr = phaseFunc;
                return true;
            }
        }

    }
    return false;
}