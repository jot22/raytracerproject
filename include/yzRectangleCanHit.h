////
//// Created by ap on 8/2/19.
////
//
//#ifndef RAYTRACER_YZRECTANGLECANHIT_H
//#define RAYTRACER_YZRECTANGLECANHIT_H
//
//#include "canHitGeneric.h"
//
//class yzRectangleCanHit : public canHitGeneric {
//public:
//
//    yzRectangleCanHit() {}
//
//    yzRectangleCanHit(float _y0,
//                      float _y1,
//                      float _z0,
//                      float _z1,
//                      float _k,
//                      material *mat) {
//        y0 = _y0;
//        y1 = _y1;
//        z0 = _z0;
//        z1 = _z1;
//        k = _k;
//        mp = mat;
//    }
//
//    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
//
//    bool bounding_box(float t0, float t1, aabb &box) const override {
//        box = aabb(vec3(k - 0.0001f, y0, z0), vec3(k + 0.0001f, y1, z1));
//        return true;
//    }
//
//    material *mp;
//    float y0, y1, z0, z1, k;
//};
//
//bool yzRectangleCanHit::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
//    float t = (k - r.origin().x()) / r.direction().x();
//    if (t < t_min || t > t_max) {
//        return false;
//    }
//    float y = r.origin().y() + t * r.direction().y();
//    float z = r.origin().z() + t * r.direction().z();
//
//    if (y < y0 || y > y1 || z < z0 || z > z1) {
//        return false;
//    }
//    rec.u = (y - y0) / (y1 - y0);
//    rec.v = (z - z0) / (z1 - z0);
//    rec.t = t;
//    rec.mat_ptr = mp;
//    rec.p = r.point_at_param(t);
//    rec.normal = vec3(1, 0, 0);
//    return true;
//}
//
//#endif //RAYTRACER_YZRECTANGLECANHIT_H
