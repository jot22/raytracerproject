//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_BVHNODE_H
#define RAYTRACER_BVHNODE_H

#include "canHitGeneric.h"


using namespace std;

//A Class that allows for the ability to render many,many objects with good performance
//Affords a huge speed up for scenes with many objects, may be slower with few objects
class bvhNode : public canHitGeneric {
public:
    //Default constructor for bvhNode
    bvhNode() = default;

    //Initializes bvhNode with list, list size, and times
    bvhNode(canHitGeneric **l, int n, float time0, float time1);

    //Destructor for bvnNode
    ~bvhNode() {
        if (destruct) {
            delete left;
            delete right;
        }
    }

    //Determines if ray hits or not
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    //Determines if bounding box is valid or not
    bool bounding_box(float t0, float t1, aabb &box) const override;

    //Variables for bvhNode
    canHitGeneric *left{};
    canHitGeneric *right{};
    aabb boxX;
    bool destruct;
};

//Determines if bounding box is valid or not
bool bvhNode::bounding_box(float t0, float t1, aabb &box) const {
    box = boxX;
    return true;
}

//Checks if a ray of light hits the bounding box or not, Splits into two parts, a left and right
bool bvhNode::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    if (boxX.hit(r, t_min, t_max)) {
        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right) {
            if (left_rec.t < right_rec.t) {
                rec = left_rec;
            } else {
                rec = right_rec;
            }
            return true;
        } else if (hit_left) {
            rec = left_rec;
            return true;
        } else if (hit_right) {
            rec = right_rec;
            return true;
        }
        return false;
    }
    return false;
}

//Compares the Bounding Box in the X-Axis
int box_x_compare(const void *a, const void *b) {
    aabb box_left, box_right;
    canHitGeneric *ah = *(canHitGeneric **) a;
    canHitGeneric *bh = *(canHitGeneric **) b;
    if (!ah->bounding_box(0, 0, box_left) ||
        !bh->bounding_box(0, 0, box_right)) {
        //std::cout << "Error in BVH Box World\n";
    }
    if (box_left.min().x() - box_right.min().x() < 0.0) {
        return -1;
    }
    return 1;

}

//Compares the Bounding Box in the Y-Axis
int box_y_compare(const void *a, const void *b) {
    aabb box_left, box_right;
    canHitGeneric *ah = *(canHitGeneric **) a;
    canHitGeneric *bh = *(canHitGeneric **) b;
    if (!ah->bounding_box(0, 0, box_left) ||
        !bh->bounding_box(0, 0, box_right)) {
        //std::cout << "Error in BVH Box World\n";
    }
    if (box_left.min().y() - box_right.min().y() < 0.0) {
        return -1;
    }
    return 1;
}


//Compares the Bounding Box in the Z-Axis
int box_z_compare(const void *a, const void *b) {
    aabb box_left, box_right;
    canHitGeneric *ah = *(canHitGeneric **) a;
    canHitGeneric *bh = *(canHitGeneric **) b;
    if (!ah->bounding_box(0, 0, box_left) ||
        !bh->bounding_box(0, 0, box_right)) {
        //std::cerr << "Error in BVH Box World\n";
    }
    if (box_left.min().z() - box_right.min().z() < 0.0) {
        return -1;
    }
    return 1;
}

//Randomly chooses an axis
//Sorts the passed in canHitGeneric and puts each half in each subtree
bvhNode::bvhNode(canHitGeneric **l, int n, float time0, float time1) {
    destruct = true;
    int axis = int(3 * (rand() / (RAND_MAX + 1.0)));
    if (axis == 0) {
        qsort(l, n, sizeof(canHitGeneric *), box_x_compare);
    } else if (axis == 1) {
        qsort(l, n, sizeof(canHitGeneric *), box_y_compare);
    } else {
        qsort(l, n, sizeof(canHitGeneric *), box_z_compare);
    }
    if (n == 1) {
        left = right = l[0];
        destruct = false;
    } else if (n == 2) {
        left = l[0];
        right = l[1];
        destruct = false;
    } else {
        left = new bvhNode(l, n / 2, time0, time1);
        right = new bvhNode(l + n / 2, n - n / 2, time0, time1);
    }

    aabb box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) ||
        !right->bounding_box(time0, time1, box_right)) {
        //std::cerr << "ERR BOX WORLD\n";
    }

    boxX = surrounding_box(box_left, box_right);

}


#endif //RAYTRACER_BVHNODE_H
