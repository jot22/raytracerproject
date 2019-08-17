//
// Created by ap on 7/31/19.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "ray.h"

//Abstracts all Camera functionality in this class, handling view location, view position, aperture,
//field of view and such.
class camera {
public:

    //Initializes camera with field of view, aspect, look from, look at, up vector, aperture, focus distance,
    // and times
    camera(float vFOV,
           float aspect,
           vec3 lookFrom,
           vec3 lookAt,
           vec3 vUp,
           float aperture,
           float focus_dist,
           float t0,
           float t1) {

        lens_radius = aperture / 2;


        float theta = vFOV * Pi / 180.0f;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;

        origin = lookFrom;
        w = unit_vector(lookFrom - lookAt);
        uU = unit_vector(cross(vUp, w));
        vV = cross(w, uU);

        lower_left_corner = origin - half_width * uU * focus_dist - half_height * vV * focus_dist - w * focus_dist;

        horizontal = 2 * half_width * uU * focus_dist;
        vertical = 2 * half_height * vV * focus_dist;

        time0 = t0;
        time1 = t1;

        //lower_left_corner =  vec3(-2.0f, -1.0f, -1.0f);
        //horizontal = vec3(4.0, 0.0, 0.0);
        //vertical = vec3(0.0, 2.0, 0.0);
        //origin = vec3(0.0, 0.0, 0.0);
    }

    //Calculates a Ray, given all supplied inputs
    ray get_ray(float u, float v) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = uU * rd.x() + vV * rd.y();

        float time = time0 + (rand() / (RAND_MAX + 1.0)) * (time1 - time0);

        return {origin + offset, lower_left_corner + u * horizontal + v * vertical - origin - offset, time};
    }

    //Variables for camera class
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 uU, vV, w;
    float lens_radius;
    float time0, time1;

private:
    //Helps randomly generate a ray of light, for our motion blur feature.
    const vec3 random_in_unit_disk() {
        vec3 p;
        do {
            p = 2.0f * vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), 0) - vec3(1, 1, 0);
        } while (dot(p, p) >= 1.0);
        return p;
    }
};

#endif //RAYTRACER_CAMERA_H
