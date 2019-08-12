//
// Created by ap on 8/1/19.
//

#ifndef RAYTRACER_CHECKERBOARDTEXTURE_H
#define RAYTRACER_CHECKERBOARDTEXTURE_H

#include "texture.h"

class checkerBoardTexture: public texture{
public:
    checkerBoardTexture() = default;

    ~checkerBoardTexture() override {
        delete[] odd;
        delete[] even;
    }

    checkerBoardTexture(texture *t0,texture *t1){
        odd = t1;
        even = t0;
    }

    vec3 value(float u, float v, const vec3 &p) const override {
        float sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
        if(sines < 0){
            return odd->value(u,v,p);
        }
        return even->value(u,v,p);
    }
    texture *odd;
    texture *even;
};

#endif //RAYTRACER_CHECKERBOARDTEXTURE_H
