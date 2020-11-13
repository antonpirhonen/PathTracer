#include "Triangle.hpp"

Triangle::Triangle(Material& material, Vec3 v0, Vec3 v1, Vec3 v2) 
  : Body(material), v0_(v0), v1_(v1), v2_(v2) {
    auto v3 = v2 - v0;
    auto normal = (v1 - v0).CrossProduct(v3);
    normal.Normalize();
    unit_normal_ = normal;
  }


void Triangle::Reflect(Ray &ray, Vec3 &new_origin) {
  if (material_.GetLuminosity()){
    ray.SetFinished();  
    ray.SetNewColor(GetMaterial().GetColor());
  }
  else {
    Vec3 normal;
    Vec3 old_direction = ray.GetDirection();
    float dot_product = old_direction.DotProduct(unit_normal_);
    Vec3 new_direction = old_direction-2.0*unit_normal_*dot_product;  
    new_direction.Normalize();
    ray.RemoveColor(material_.GetColorRem());
    ray.SetNewOrigin(new_origin);
    ray.SetNewDirection(new_direction);
  }
}

float Triangle::FindCollision(Ray& ray) const {
  float tolerance = 0.00001;
  Vec3 edge0 = v1_ - v0_;
  Vec3 edge1 = v2_ - v0_;

  Vec3 p_vec = ray.GetDirection().CrossProduct(edge1);
  Vec3 t_vec = ray.GetOrigin() - v0_;
  Vec3 q_vec = t_vec.CrossProduct(edge0);

  //parallel
  float determinant = edge0.DotProduct(p_vec);
  if (std::abs(determinant) < tolerance){
    return -1;
  }
  float inverse_determinant = 1/determinant;

  //miss on one side
  float u = t_vec.DotProduct(p_vec) * inverse_determinant;
  if (u < 0 || u > 1){
    return -1;
  }

  //miss on the second or the third side
  float v = ray.GetDirection().DotProduct(q_vec) * inverse_determinant;
  if (v < 0 || u + v > 1){
    return -1;
  }

  //hits triangle
  float distance = edge1.DotProduct(q_vec) * inverse_determinant;
  if (distance > tolerance){
    return edge1.DotProduct(q_vec) * inverse_determinant;
  }
  else {
  //triangle is behind the starting point, or the same triangle where the ray started
    return -1;
  }

}

