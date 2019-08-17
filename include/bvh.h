//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include "canHitGeneric.h"
#include "bvhNode.h"

//bvh provides a root node for bvh node so that a bvh can be deleted
class bvh : public canHitGeneric {
public:
    //Default constructor for bvh
    bvh() = default;

    //Initializes bvhNode with list, list size, and times
    bvh(canHitGeneric **l, int n, float time0, float time1) {
        list = l;
        node = new bvhNode(l, n, time0, time1);
        list_size = n;
    }

    //Destructor for bvh
    ~bvh() {
        delete node;
        for (int i = 0; i < list_size; i++) {
            delete list[i];
        }
        delete[] list;
    }

    //determines if ray hits bvh or not
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
        return node->hit(r, t_min, t_max, rec);
    }

    //Determines if bounding box is valid or not for bvh
    bool bounding_box(float t0, float t1, aabb &box) const {
        return node->bounding_box(t0, t1, box);
    }

    //Variables for bvh
    canHitGeneric *node;
    canHitGeneric **list;
    aabb boxX;
    int list_size;
};

#endif //RAYTRACER_BVH_H