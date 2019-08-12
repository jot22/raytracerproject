//
// Created by ap on 7/30/19.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class ray{
public:
    ray() = default;

    ray(const vec3& a, const vec3&b, float ti = 0.0f){
        A = a;
        B = b;
        _time = ti;
    }
    vec3 origin() const{
        return A;
    }

    vec3 direction() const{
        return B;
    }

    /**
     * p(t) = A+t*B
     * A = Ray origin
     * B = Ray Direction
     * t = movement value
     */
    vec3 point_at_param(float t) const{
        return A+t*B;
    }

    float time() const {
        return _time;
    }

    vec3 A;
    vec3 B;
    float _time;
};

#endif //RAYTRACER_RAY_H
