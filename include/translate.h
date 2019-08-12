//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_TRANSLATE_H
#define RAYTRACER_TRANSLATE_H

#include "canHitGeneric.h"

class translate: public canHitGeneric{
public:
    translate(canHitGeneric *p, const vec3& displacement){
        ptr = p;
        offset = displacement;
    }

    bool bounding_box(float t0, float t1, aabb &box) const override;

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    vec3 offset;
    canHitGeneric *ptr;
};

bool translate::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    ray moved_r(r.origin()-offset,r.direction(),r.time());
    if(ptr->hit(moved_r,t_min,t_max,rec)){
        rec.p+=offset;
        return true;
    }
    return false;
}

bool translate::bounding_box(float t0, float t1, aabb &box) const {
    if(ptr->bounding_box(t0,t1,box)){
        box = aabb(box.min()+offset,box.max()+offset);
        return true;
    }
    return false;
}

#endif //RAYTRACER_TRANSLATE_H
