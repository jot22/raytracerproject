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

//A Class to Purely create a Rectangular 6 Sided 3D Box.
class boxCanHit : public canHitGeneric {
public:
    //Default constructor for boxCanHit
    boxCanHit() {}

    //Initializes boxCanHit with input vectors and material
    boxCanHit(const vec3 &p0, const vec3 &p1, material *ptr);

    //Returns if ray hits or not
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    //Returns if bounding box is valid or not
    bool bounding_box(float t0, float t1, aabb &box) const override {
        box = aabb(pMin, pMax);
        return true;
    }

    //Destructor for boxCanHit
    ~boxCanHit() {
        delete lPtr;
        delete mp;
    }

    //Variables for boxCanHit class
    canHitGeneric *lPtr;
    material *mp;
    vec3 pMin, pMax;
};

//Checks if a ray of light hits the generated box or not
bool boxCanHit::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    return lPtr->hit(r, t_min, t_max, rec);
}

//Creates the 6 Sided Rectangular Box
boxCanHit::boxCanHit(const vec3 &p0, const vec3 &p1, material *ptr) {
    pMax = p1;
    pMin = p0;
    mp = ptr;
    auto **hitList = new canHitGeneric *[6];
    hitList[0] = new rectangleCanHit(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr, true);
    hitList[1] = new flipNormals(new rectangleCanHit(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr, true));
    hitList[2] = new xzRectangleCanHit(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr, true);
    hitList[3] = new flipNormals(new xzRectangleCanHit(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr, true));
    hitList[4] = new yzRectangleCanHit(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr, true);
    hitList[5] = new flipNormals(new yzRectangleCanHit(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr, true));
    lPtr = new canHitGenericList(hitList, 6);
}

#endif //RAYTRACER_BOXCANHIT_H
