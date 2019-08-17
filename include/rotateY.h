//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_ROTATEY_H
#define RAYTRACER_ROTATEY_H

#include <cfloat>
#include "canHitGeneric.h"

//Rotates a canHitGeneric object about the Y-Axis
class rotateY : public canHitGeneric {
public:
    //initializes rotateY with canHitGeneric and angle
    rotateY(canHitGeneric *p, float angle);

    //destructor for rotateY
    ~rotateY() {
        delete ptr;
    }

    //determines if bounding box is valid or not
    bool bounding_box(float t0, float t1, aabb &box) const override {
        box = bBox;
        return hasBox;
    }

    //determines if ray hits rotateY or not
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    //variables for rotateY
    float sinTheta;
    float cosTheta;
    bool hasBox;
    aabb bBox;
    canHitGeneric *ptr;
};

//Initializes rotateY with canHitGeneric and angle
rotateY::rotateY(canHitGeneric *p, float angle) {
    ptr = p;
    float rad = (Pi / 180.0f) * angle;
    sinTheta = sin(rad);
    cosTheta = cos(rad);
    hasBox = ptr->bounding_box(0, 1, bBox);
    vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
    vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (int i = 0; i < 2; i++) {
        for (int k = 0; k < 2; k++) {
            for (int p = 0; p < 2; p++) {
                float x = i * bBox.max().x() + (1.0f - i) * bBox.min().x();
                float y = k * bBox.max().y() + (1.0f - k) * bBox.min().y();
                float z = p * bBox.max().z() + (1.0f - p) * bBox.min().z();

                float newX = cosTheta * x + sinTheta * z;
                float newZ = -sinTheta * x + cosTheta * z;
                vec3 testVec(newX, y, newZ);
                for (int u = 0; u < 3; u++) {
                    if (testVec[u] > max[u]) {
                        max[u] = testVec[u];
                    }
                    if (testVec[u] < min[u]) {
                        min[u] = testVec[u];
                    }
                }
            }
        }
    }
    bBox = aabb(min, max);
}

//determines if ray hits rotateY or not
bool rotateY::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 origin = r.origin();
    vec3 dir = r.direction();
    origin[0] = cosTheta * r.origin()[0] - sinTheta * r.origin()[2];
    origin[2] = sinTheta * r.origin()[0] + cosTheta * r.origin()[2];

    dir[0] = cosTheta * r.direction()[0] - sinTheta * r.direction()[2];
    dir[2] = sinTheta * r.direction()[0] + cosTheta * r.direction()[2];

    ray rotated_r(origin, dir, r.time());

    if (ptr->hit(rotated_r, t_min, t_max, rec)) {
        vec3 p = rec.p;
        vec3 normal = rec.normal;
        p[0] = cosTheta * rec.p[0] + sinTheta * rec.p[2];
        p[2] = -sinTheta * rec.p[0] + cosTheta * rec.p[2];

        normal[0] = cosTheta * rec.normal[0] + sinTheta * rec.normal[2];
        normal[2] = -sinTheta * rec.normal[0] + cosTheta * rec.normal[2];
        rec.p = p;
        rec.normal = normal;
        return true;
    }
    return false;
}

#endif //RAYTRACER_ROTATEY_H
