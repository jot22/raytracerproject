//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_XZRECTANGLECANHIT_H
#define RAYTRACER_XZRECTANGLECANHIT_H

#include "canHitGeneric.h"

//Like a regular rectangle canHitGeneric sub-object, but on the basis of X-Z positioning.

class xzRectangleCanHit: public canHitGeneric{
public:
    xzRectangleCanHit(){}
    xzRectangleCanHit(float _x0,
                      float _x1,
                      float _z0,
                      float _z1,
                      float _k,
                      material *mat) {
        x0 = _x0;
        x1 = _x1;
        z0 = _z0;
        z1 = _z1;
        k = _k;
        mp = mat;
    }
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
    bool bounding_box(float t0,float t1, aabb& box) const override{
        box = aabb(vec3(x0,k-0.0001f,z0),vec3(x1,k+0.0001f,z1));
        return true;
    }
    material *mp;
    float x0, x1, z0, z1, k;
};

bool xzRectangleCanHit::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    float t = (k-r.origin().y()) / r.direction().y();
    if(t < t_min || t > t_max){
        return false;
    }
    float x = r.origin().x()+t*r.direction().x();
    float z = r.origin().z()+t*r.direction().z();

    if(x < x0 || x > x1 || z < z0 || z > z1){
        return false;
    }
    rec.u = (x-x0) / (x1-x0);
    rec.v = (z-z0) / (z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_param(t);
    rec.normal = vec3(0,1,0);
    return true;
}

#endif //RAYTRACER_XZRECTANGLECANHIT_H
