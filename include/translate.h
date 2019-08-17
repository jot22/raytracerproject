//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_TRANSLATE_H
#define RAYTRACER_TRANSLATE_H

#include "canHitGeneric.h"

//A way of translating a canHitGeneric object to a different position in the world
class translate : public canHitGeneric {
public:
    //initialzes translate with canHitGeneric and offset
    translate(canHitGeneric *p, const vec3 &displacement) {
        ptr = p;
        offset = displacement;
    }

    //destructor for translate
    ~translate() {
        delete ptr;
    }

    //determines if bounding box is valid or not for translate
    bool bounding_box(float t0, float t1, aabb &box) const override;

    //determines if ray hits translate or not
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    //variables for translate
    vec3 offset;
    canHitGeneric *ptr;
};

//Moves the hit position of the object from it's original coordinates, to the new ones.
bool translate::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (ptr->hit(moved_r, t_min, t_max, rec)) {
        rec.p += offset;
        return true;
    }
    return false;
}

//Moves the bounding box location of the object from the original coordinates, to the new ones
bool translate::bounding_box(float t0, float t1, aabb &box) const {
    if (ptr->bounding_box(t0, t1, box)) {
        box = aabb(box.min() + offset, box.max() + offset);
        return true;
    }
    return false;
}

#endif //RAYTRACER_TRANSLATE_H
