//
// Created by ap on 7/30/19.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

//Base class for a ray of "light", provides getters and a calculation function for a point at t
class ray {
public:
    //Default constructor for ray
    ray() = default;

    //Initializes ray with origin, direction, and time
    ray(const vec3 &a, const vec3 &b, float ti = 0.0f) {
        A = a;
        B = b;
        _time = ti;
    }

    //Returns origin vector of ray
    vec3 origin() const {
        return A;
    }

    //Returns direction vector of ray
    vec3 direction() const {
        return B;
    }

    /**
     * p(t) = A+t*B
     * A = Ray origin
     * B = Ray Direction
     * t = movement value
     */
    vec3 point_at_param(float t) const {
        return A + t * B;
    }

    //returns time of ray
    float time() const {
        return _time;
    }

    //variables for ray
    vec3 A;
    vec3 B;
    float _time;
};

#endif //RAYTRACER_RAY_H
