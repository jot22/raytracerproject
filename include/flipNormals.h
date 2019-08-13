//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_FLIPNORMALS_H
#define RAYTRACER_FLIPNORMALS_H

#include "canHitGeneric.h"

class flipNormals : public canHitGeneric {
public:
    flipNormals() {}

    flipNormals(canHitGeneric *p) {
        ptr = p;
    }

    ~flipNormals() {
        delete ptr;
    }

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override {
        if (ptr->hit(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        }
        return false;
    }

    bool bounding_box(float t0, float t1, aabb &box) const override {
        return ptr->bounding_box(t0, t1, box);
    }

    canHitGeneric *ptr;

};

#endif //RAYTRACER_FLIPNORMALS_H
