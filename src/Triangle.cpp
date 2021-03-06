#include <iostream>

#include "Triangle.hpp"
#include <iostream>

Triangle::Triangle(Material* material, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 n0, Vec3 n1, Vec3 n2)
    : Body(material), v0_(v0), v1_(v1), v2_(v2), n0_(n0), n1_(n1), n2_(n2), using_vertex_normals_(true) { }

Triangle::Triangle(Material* material, Vec3 v0, Vec3 v1, Vec3 v2)
    : Body(material), v0_(v0), v1_(v1), v2_(v2), using_vertex_normals_(false) {
    auto v3 = v2 - v0;
    auto normal = (v1 - v0).CrossProduct(v3);
    normal.Normalize();
    unit_normal_ = normal;
}


void Triangle::Reflect(Ray &ray, Vec3 &new_origin, float u, float v) {
    if (material_->GetLuminosity()){
	ray.SetFinished();  
	ray.RemoveColor(material_->GetColor());
    }
    else {
	ray.RemoveColor(material_->GetColorRem());
	ray.SetNewOrigin(new_origin);
	Vec3 new_direction = material_->Reflect(ray.GetDirection(), GetNormalAt(new_origin, u, v));
	ray.SetNewDirection(new_direction);
    }
}

std::tuple<float, float, float> Triangle::FindCollision(Ray& ray) const {
    float tolerance = 0.00001;
    Vec3 edge0 = v1_ - v0_;
    Vec3 edge1 = v2_ - v0_;
    Vec3 p_vec = ray.GetDirection().CrossProduct(edge1);
    Vec3 t_vec = ray.GetOrigin() - v0_;
    Vec3 q_vec = t_vec.CrossProduct(edge0);

    //parallel
    float determinant = edge0.DotProduct(p_vec);
    if (std::abs(determinant) < tolerance){
	return std::make_tuple(-1, -1, -1);
    }
    float inverse_determinant = 1/determinant;

    //miss on one side
    float u = t_vec.DotProduct(p_vec) * inverse_determinant;
    if (u < 0 || u > 1){
	return std::make_tuple(-1, -1, -1);
    }

    //miss on the second or the third side
    float v = ray.GetDirection().DotProduct(q_vec) * inverse_determinant;
    if (v < 0 || u + v > 1){
	return std::make_tuple(-1, -1, -1);
    }

    //hits triangle
    float distance = edge1.DotProduct(q_vec) * inverse_determinant;
    if (distance > tolerance){
	return std::make_tuple(distance, u, v);
    }
    else {
	//triangle is behind the starting point, or the same triangle where the ray started
	return std::make_tuple(-1, -1, -1);
    }

}

Vec3 Triangle::GetNormalAt(Vec3& collision_point, float u, float v) {
    if (using_vertex_normals_) {
	return (1-u-v) * n0_ + u * n1_ + v * n2_;
    }
    return unit_normal_;
}

void Triangle::MoveBy(Vec3& v) {
    v0_ = v0_ + v;
    v1_ = v1_ + v;
    v2_ = v2_ + v;
}

void Triangle::ScaleBy(float c) {
    v0_ = v0_ * c;
    v1_ = v1_ * c;
    v2_ = v2_ * c;
}

void Triangle::RotateAroundXAxisBy(float deg) {
    v0_ = v0_.RotateAroundXAxis(deg);
    v1_ = v1_.RotateAroundXAxis(deg);
    v2_ = v2_.RotateAroundXAxis(deg);
    n0_ = n0_.RotateAroundXAxis(deg);
    n1_ = n1_.RotateAroundXAxis(deg);
    n2_ = n2_.RotateAroundXAxis(deg);
    unit_normal_ = unit_normal_.RotateAroundXAxis(deg);
}

void Triangle::RotateAroundYAxisBy(float deg) {
    v0_ = v0_.RotateAroundYAxis(deg);
    v1_ = v1_.RotateAroundYAxis(deg);
    v2_ = v2_.RotateAroundYAxis(deg);
    n0_ = n0_.RotateAroundYAxis(deg);
    n1_ = n1_.RotateAroundYAxis(deg);
    n2_ = n2_.RotateAroundYAxis(deg);
    unit_normal_ = unit_normal_.RotateAroundYAxis(deg);
}

void Triangle::RotateAroundZAxisBy(float deg) {
    v0_ = v0_.RotateAroundZAxis(deg);
    v1_ = v1_.RotateAroundZAxis(deg);
    v2_ = v2_.RotateAroundZAxis(deg);
    n0_ = n0_.RotateAroundZAxis(deg);
    n1_ = n1_.RotateAroundZAxis(deg);
    n2_ = n2_.RotateAroundZAxis(deg);
    unit_normal_ = unit_normal_.RotateAroundZAxis(deg);    
}
