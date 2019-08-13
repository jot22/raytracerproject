//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_BOXCANHIT_H
#define RAYTRACER_BOXCANHIT_H

#include "canHitGeneric.h"
#include "rectangleCanHit.h"
#include "flipNormals.h"
#include "xzRectangleCanHit.h"
#include "yzRectangleCanHit.h"
#include "canHitGenericList.h"

class boxCanHit : public canHitGeneric {
public:
    boxCanHit() {}

    boxCanHit(const vec3 &p0, const vec3 &p1, material *ptr);

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    bool bounding_box(float t0, float t1, aabb &box) const override {
        box = aabb(pMin, pMax);
        return true;
    }

    ~boxCanHit() {
        delete lPtr;
    }

    canHitGeneric *lPtr;
    vec3 pMin, pMax;
};

bool boxCanHit::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    return lPtr->hit(r, t_min, t_max, rec);
}

boxCanHit::boxCanHit(const vec3 &p0, const vec3 &p1, material *ptr) {
    pMax = p1;
    pMin = p0;
    auto **hitList = new canHitGeneric *[6];
    hitList[0] = new rectangleCanHit(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr);
    hitList[1] = new flipNormals(new rectangleCanHit(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
    hitList[2] = new xzRectangleCanHit(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
    hitList[3] = new flipNormals(new xzRectangleCanHit(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
    hitList[4] = new yzRectangleCanHit(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);
    hitList[5] = new flipNormals(new yzRectangleCanHit(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
    lPtr = new canHitGenericList(hitList, 6);
}

#endif //RAYTRACER_BOXCANHIT_H
