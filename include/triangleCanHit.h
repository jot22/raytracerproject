//
// Created by ap on 8/3/19.
//

#ifndef RAYTRACER_TRIANGLECANHIT_H
#define RAYTRACER_TRIANGLECANHIT_H

#include <tgmath.h>
#include "canHitGeneric.h"

class triangleCanHit : public canHitGeneric {
public:
    triangleCanHit() = default;

    triangleCanHit(vec3 f0, vec3 f1, vec3 f2, shared_ptr<material> m) {
        face0 = f0;
        face1 = f1;
        face2 = f2;
        mat = m;

    }

    ~triangleCanHit() override {
       // delete[] mat;
//        delete &mat;
//        delete[] &face0;
//        delete[] &face1;
//        delete[] &face2;
    }

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    bool bounding_box(float t0, float t1, aabb &box) const override;

    vec3 face0{};
    vec3 face1{};
    vec3 face2{};
    shared_ptr<material> mat{};
    //material *mat{};
};

bool triangleCanHit::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    float epsilon = 0.0000001f;

    vec3 a = face1 - face0;
    vec3 b = face2 - face0;
    vec3 c = cross(r.direction(), b);

    float denom = dot(a, c);

    if (denom < epsilon) { return false; }

    vec3 d = r.origin() - face0;
    float u = dot(d, c) / denom;
    if (u < 0.0f || u > 1.0f) { return false; }

    vec3 e = cross(d, a);
    float v = dot(r.direction(), e) / denom;
    if (v < 0.0f || u + v > 1.0f) { return false; }

    float t = dot(b, e) / denom;

    rec.u = u;
    rec.v = v;
    rec.t = t;
    rec.mat_ptr = mat;
    rec.p = r.point_at_param(t);
    rec.normal = unit_vector(cross(a, b));
    return true;

}

bool triangleCanHit::bounding_box(float t0, float t1, aabb &box) const {
    float minx = min(min(face0.x(), face1.x()), face2.x());
    float miny = min(min(face0.y(), face1.y()), face2.y());
    float minz = min(min(face0.z(), face1.z()), face2.z());
    float maxx = max(max(face0.x(), face1.x()), face2.x());
    float maxy = max(max(face0.y(), face1.y()), face2.y());
    float maxz = max(max(face0.z(), face1.z()), face2.z());

    box = aabb(vec3(minx, miny, minz), vec3(maxx, maxy, maxz));

    return true;
}

#endif //RAYTRACER_TRIANGLECANHIT_H
