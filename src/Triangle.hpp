#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Body.hpp"
#include "Vec3.hpp"

class Triangle : public Body {

public:
    Triangle(Material* material, Vec3 v0, Vec3 v1, Vec3 v2);
    Triangle(Material* material, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 n0, Vec3 n1, Vec3 n2);

    Triangle(Triangle& tr) : Body(tr.material_) {
        v0_ = tr.v0_;
        v1_ = tr.v1_;
        v2_ = tr.v2_;
        n0_ = tr.n0_;
        n1_ = tr.n1_;
        n2_ = tr.n2_;
        unit_normal_ = tr.unit_normal_;
    }
    Triangle(const Triangle& tr) : Body(tr.material_) {
        v0_ = tr.v0_;
        v1_ = tr.v1_;
        v2_ = tr.v2_;
        n0_ = tr.n0_;
        n1_ = tr.n1_;
        n2_ = tr.n2_;
        unit_normal_ = tr.unit_normal_;
    }
    Triangle operator=(Triangle& tr) {
        v0_ = tr.v0_;
        v1_ = tr.v1_;
        v2_ = tr.v2_;
        n0_ = tr.n0_;
        n1_ = tr.n1_;
        n2_ = tr.n2_;
        unit_normal_ = tr.unit_normal_;
        material_ = tr.material_;
        return *this;
    }
    Triangle operator=(const Triangle& tr) {
        v0_ = tr.v0_;
        v1_ = tr.v1_;
        v2_ = tr.v2_;
        n0_ = tr.n0_;
        n1_ = tr.n1_;
        n2_ = tr.n2_;
        unit_normal_ = tr.unit_normal_;
        material_ = tr.material_;
        return *this;
    }

    std::tuple<Vec3, Vec3, Vec3> GetVertices() { return std::make_tuple(v0_, v1_, v2_); }
    
    std::tuple<float, float, float> FindCollision(Ray &ray) const;
    void Reflect(Ray &ray, Vec3 &new_origin, float, float);
    Vec3 GetNormalAt(Vec3&, float, float);

    void MoveBy(Vec3& v);
    void ScaleBy(float c);
    void RotateAroundXAxisBy(float deg);
    void RotateAroundYAxisBy(float deg);
    void RotateAroundZAxisBy(float deg);

private:
    Vec3 v0_;
    Vec3 v1_;
    Vec3 v2_;
    Vec3 n0_;
    Vec3 n1_;
    Vec3 n2_;
    Vec3 unit_normal_;
};

#endif
