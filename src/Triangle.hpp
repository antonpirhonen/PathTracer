#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Body.hpp"
#include "Vec3.hpp"

class Triangle : public Body {

public:
    Triangle(Material& material, Vec3 v0, Vec3 v1, Vec3 v2);
    float FindCollision(Ray &ray) const;
    void Reflect(Ray &ray, Vec3 &new_origin);

private:
    Vec3 v0_;
    Vec3 v1_;
    Vec3 v2_;
    Vec3 unit_normal_;
};

#endif
