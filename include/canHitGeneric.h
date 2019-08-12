//
// Created by ap on 7/31/19.
//
#ifndef RAYTRACER_CANHIT_H
#define RAYTRACER_CANHIT_H

#define PI 3.14159265359f;

#include "aabb.h"

class material;

const float Pi = PI;

struct hit_record {
    float t;
    float u;
    float v;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class canHitGeneric {
public:
    //Virtual means function can be changed at run-time,
    //by a child class that derives from the top level parent class
    //https://www.geeksforgeeks.org/virtual-function-cpp/
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
    virtual bool bounding_box(float t0,float t1, aabb& box) const = 0;

};

void get_sphere_uv(const vec3& p, float &u, float &v){
    float phi = atan2(p.z(),p.x());
    float theta = asin(p.y());
    u = 1.0f-(phi+Pi) / (2.0f*Pi);
    v = (theta + Pi/2) / Pi;
}


#endif //RAYTRACER_CANHIT_H
