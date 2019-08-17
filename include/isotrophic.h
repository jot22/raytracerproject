//
// Created by ap on 8/2/19.
//

#ifndef RAYTRACER_ISOTROPHIC_H
#define RAYTRACER_ISOTROPHIC_H

#include "material.h"
#include "texture.h"

//Class for isotrophic materials
class isotrophic : public material {
public:
    //Initializes isotrophic with texture
    isotrophic(texture *a) {
        albedo = a;
    }

    //Destructor for isotropic
    ~isotrophic() {
        delete albedo;
    }

    //Scatters ray for isotrophic
    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        scattered = ray(rec.p, random_in_unit_sphere());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

    //Variable for isotrophic
    texture *albedo;
private:
    //Function for random_in_unit_sphere
    vec3 random_in_unit_sphere() const {
        vec3 p;
        do {
            p = 2.0f * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) -
                vec3(1, 1, 1);
        } while (p.squared_length() >= 1.0);
        return p;
    }
};

#endif //RAYTRACER_ISOTROPHIC_H