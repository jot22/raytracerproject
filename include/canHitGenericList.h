//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_CANHITGENERICLIST_H
#define RAYTRACER_CANHITGENERICLIST_H

#include "canHitGeneric.h"

class canHitGenericList : public canHitGeneric {
public:
    canHitGenericList() = default;

    canHitGenericList(canHitGeneric **l, int n) {
        list = l;
        list_size = n;
    };

    ~canHitGenericList() {
        for (int i = 0; i < list_size; ++i) {
            delete list[i];
        }
    }

    bool hit(const ray &r, float tMin, float tMax, hit_record &rec) const override;

    bool bounding_box(float t0, float t1, aabb &box) const override;

    canHitGeneric **list;
    int list_size;
};

bool canHitGenericList::bounding_box(float t0, float t1, aabb &box) const {
    if (list_size < 1) {
        return false;
    }

    aabb tempBox;
    bool first_true = list[0]->bounding_box(t0, t1, tempBox);
    if (!first_true) {
        return false;
    } else {
        box = tempBox;
    }
    for (int i = 1; i < list_size; i++) {
        if (list[0]->bounding_box(t0, t1, tempBox)) {
            box = surrounding_box(box, tempBox);
        } else {
            return false;
        }

    }
    return true;
}

bool canHitGenericList::hit(const ray &r, float tMin, float tMax, hit_record &rec) const {
    hit_record temp_rec;
    bool hasHit = false;
    double closestTry = tMax;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, tMin, closestTry, temp_rec)) {
            hasHit = true;
            closestTry = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hasHit;
}

#endif //RAYTRACER_CANHITGENERICLIST_H
