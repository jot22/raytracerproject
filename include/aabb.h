//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "ray.h"

//Returns the min of the two input floats
inline float ffmin(float a, float b) {
    return a < b ? a : b;
}

//Returns the max of the two input floats
inline float ffmax(float a, float b) {
    return a > b ? a : b;
}

/**
 * An Axis-Aligned Bounding Box Class (AABB)
 */
class aabb {
public:
    //Default constructor for bounding box
    aabb() = default;

    //Initializes a bounding box with a minimum (a) and maximum (b) vector
    aabb(const vec3 &a, const vec3 &b) {
        _min = a;
        _max = b;
    }

    //Returns the minimum vector for the bounding box
    vec3 min() const {
        return _min;
    }

    //Returns the maximum vector for the bounding box
    vec3 max() const {
        return _max;
    }

    //Calculates if a ray of light hits or not inside the AABB
    bool hit(const ray &r, float tMin, float tMax) const {
        for (int a = 0; a < 3; a++) {
            float t0Min = (_min[a] - r.origin()[a]) / r.direction()[a];
            float t0Max = (_max[a] - r.origin()[a]) / r.direction()[a];
            float t0 = ffmin(t0Min, t0Max);
            float t1 = ffmax(t0Min, t0Max);

            tMin = ffmax(t0, tMin);
            tMax = ffmin(t1, tMax);
            if (tMax <= tMin) {
                return false;
            }
        }
        return true;
    }


    vec3 _min;
    vec3 _max;
};

//Calculates the Surrounding Box for the AABB.
aabb surrounding_box(aabb box0, aabb box1) {
    vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
    vec3 large(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));
    return {small, large};
}


#endif //RAYTRACER_AABB_H
