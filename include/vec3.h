//
// Created by ap on 7/30/19.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <cmath>
#include <iostream>

//A homemade vector class, featuring 3 parameters (RGB or XYZ in our case)
//Provides every function required and expected of a Vector Class
class vec3 {
public:
    //default constructor for vec3
    vec3() = default;

    //initializes vec3 with input floats
    vec3(float e0, float e1, float e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    //returns x of vec3
    inline float x() const {
        return e[0];
    }

    //returns y of vec3
    inline float y() const {
        return e[1];
    }

    //returns z of vec3
    inline float z() const {
        return e[2];
    }

    //returns r of vec3
    inline float r() const {
        return e[0];
    }

    //returns g of vec3
    inline float g() const {
        return e[1];
    }

    //returns b of vec3
    inline float b() const {
        return e[2];
    }

    //returns vec3
    inline const vec3 &operator+() const {
        return *this;
    }

    //returns negative vec3
    inline vec3 operator-() const {
        return {-e[0], -e[1], -e[2]};
    }

    //returns element of vec3
    inline float operator[](int i) const {
        return e[i];
    }

    //returns element of vec3
    inline float &operator[](int i) {
        return e[i];
    }

    //adds to vec3
    inline vec3 &operator+=(const vec3 &v2);

    //subtracts to vec3
    inline vec3 &operator-=(const vec3 &v2);

    //multiplies to vec3
    inline vec3 &operator*=(const vec3 &v2);

    //divides from vec3
    inline vec3 &operator/=(const vec3 &v2);

    //scales vec3
    inline vec3 &operator*=(const float t);

    //scales vec3
    inline vec3 &operator/=(const float t);

    //gets length of vec3
    inline float length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    //squared length of vec3
    inline float squared_length() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    //makes vec3 unit vector
    inline void make_unit_vector();

    //variable for vec3
    float e[3];
};

//reads in vec3
inline std::istream &operator>>(std::istream &is, vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

//writes out vec3
inline std::ostream &operator<<(std::ostream &os, const vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

//makes vec3 unit vector
inline void vec3::make_unit_vector() {
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

//adds vec3's
inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]};
}

//subtracts vec3's
inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]};
}

//multiplies vec3's
inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]};
}

//divides vec3's
inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]};
}

//scales vec3
inline vec3 operator*(float t, const vec3 &v) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

//scales vec3
inline vec3 operator/(vec3 v, float t) {
    return {v.e[0] / t, v.e[1] / t, v.e[2] / t};
}

//scales vec3
inline vec3 operator*(const vec3 &v, float t) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

//returns dot product of two vec3's
inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

//returns cross product of two vec3's
inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return {(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
            (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
            (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])};
}

//adds vec3's
inline vec3 &vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

//multiplies vec3's
inline vec3 &vec3::operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

//divides vec3's
inline vec3 &vec3::operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

//subtracts vec3's
inline vec3 &vec3::operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

//scales vec3
inline vec3 &vec3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

//scales vec3
inline vec3 &vec3::operator/=(const float t) {
    float k = 1.0 / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

//returns vec3 unit vector
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}


#endif //RAYTRACER_VEC3_H
