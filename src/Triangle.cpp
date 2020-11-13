#include <iostream>
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
  }
  else {
    Vec3 normal;
    Vec3 old_direction = ray.GetDirection();
    float dot_product = old_direction.DotProduct(unit_normal_);
    
    if (dot_product < 0){
//      normal = unit_normal_.Reverse();
//      dot_product = -dot_product;
    }
    
    Vec3 new_direction = old_direction-2.0*unit_normal_*dot_product;  
    new_direction.Normalize();
    ray.RemoveColor(material_.GetColorRem());
    ray.SetNewOrigin(new_origin);
    ray.SetNewDirection(new_direction);
  }
}

float Triangle::FindCollision(Ray& ray) const {
//  std::cout << "FindCollision 1\n" << std::endl;
  float tolerance = 0.001;
  Vec3 edge0 = v1_ - v0_;
  Vec3 edge1 = v2_ - v0_;

  Vec3 p_vec = ray.GetDirection().CrossProduct(edge1);
  Vec3 t_vec = ray.GetOrigin() - v0_;
  Vec3 q_vec = t_vec.CrossProduct(edge0);

  float determinant = edge0.DotProduct(p_vec);
  
//  std::cout << "FindCollision Determinant =" << determinant << tolerance << std::endl;

  if (std::abs(determinant) < tolerance){
//    std::cout << "parallel, det = " << determinant << std::endl;
    return -1;
  }
  float inverse_determinant = 1/determinant;

//  std::cout << "FindCollision 3\n" << std::endl;

  float u = t_vec.DotProduct(p_vec) * inverse_determinant;
  if (u < 0 || u > 1){
//    std::cout << "ohi, u = " << u << std::endl;
    return -1;

  }

//  std::cout << "FindCollision 4\n" << std::endl;

  float v = ray.GetDirection().DotProduct(q_vec) * inverse_determinant;
  if (v < 0 || u + v > 1){
//    std::cout << "ohi, v = " << v << std::endl;
    return -1;
  }

//  std::cout << "FindCollision 5\n" << std::endl;
  float distance = edge1.DotProduct(q_vec) * inverse_determinant;
  if (distance > tolerance){
//    std::cout << "osui, etäisyys = " << edge1.DotProduct(q_vec) * inverse_determinant << std::endl;
    return edge1.DotProduct(q_vec) * inverse_determinant;
  }
  else {
//    std::cout << "sama tai taka, d = " << distance << std::endl;
    return -1;
  }

}


/*
float Triangle::FindCollision(Ray& ray) const
{
    const float EPSILON = 0.0000001;
    Vec3 vertex0 = v0_;
    Vec3 vertex1 = v1_;
    Vec3 vertex2 = v2_;
    Vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = ray.GetPath().direction_.CrossProduct(edge2);
    a = edge1.DotProduct(h);
    if (a > -EPSILON && a < EPSILON){
        return -1;    // This ray is parallel to this triangle.
    }
    f = 1.0/a;
    s = ray.GetPath().location_ - vertex0;
    u = f * s.DotProduct(h);
    if (u < 0.0 || u > 1.0){
        return -1;
    }
    q = s.CrossProduct(edge1);
    v = f * ray.GetPath().direction_.DotProduct(q);
    if (v < 0.0 || u + v > 1.0){
        return -1;
    }
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.DotProduct(q);
    if (t > EPSILON) {
        return t;
    }
    else {// This means that there is a line intersection but not a ray intersection.
        return -1;
    }
}
*/

