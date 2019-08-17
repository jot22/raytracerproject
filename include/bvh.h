//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

class bvh : public canHitGeneric {
public:
    //Default constructor for bvh
    bvh() = default;

    //Initializes bvhNode with list, list size, and times
    bvh(canHitGeneric **l, int n, float time0, float time1);

    //Destructor for bvh
    ~bvh() {
        delete node;
        delete list;
    }

    //Determines if ray hits or not
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    //Determines if bounding box is valid or not
    bool bounding_box(float t0, float t1, aabb &box) const override;

    //Variables for bvh
    canHitGeneric *node;
    canHitGeneric **list;
    aabb boxX;
};

#endif //RAYTRACER_BVH_H