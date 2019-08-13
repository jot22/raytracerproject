//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_RECTANGLECANHIT_H
#define RAYTRACER_RECTANGLECANHIT_H

#include "canHitGeneric.h"

class rectangleCanHit : public canHitGeneric {
public:
    rectangleCanHit() {}

    rectangleCanHit(float _x0,
                    float _x1,
                    float _y0,
                    float _y1,
                    float _k,
                    material *mat) {
        x0 = _x0;
        x1 = _x1;
        y0 = _y0;
        y1 = _y1;
        k = _k;
        mp = mat;
    }

    ~rectangleCanHit() {
        delete mp;
    }

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    bool bounding_box(float t0, float t1, aabb &box) const override {
        box = aabb(vec3(x0, y0, k - 0.0001f), vec3(x1, y1, k + 0.0001f));
        return true;
    }

    material *mp;
    float x0, x1, y0, y1, k;

};

bool rectangleCanHit::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    float t = (k - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max) {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float y = r.origin().y() + t * r.direction().y();

    if (x < x0 || x > x1 || y < y0 || y > y1) {
        return false;
    }
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_param(t);
    rec.normal = vec3(0, 0, 1);
    return true;
}

#endif //RAYTRACER_RECTANGLECANHIT_H
