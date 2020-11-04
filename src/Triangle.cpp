#include "Triangle.hpp"

Triangle::Triangle(Material& material, Vec3 v0, Vec3 v1, Vec3 v2) 
  : Body(material), v0_(v0), v1_(v1), v2_(v2) {
    auto v3 = v2 - v0;
    auto normal = (v1 - v0).CrossProduct(v3);
    normal.Normalize();
    unit_normal_ = normal;
  }

float Triangle::FindCollision(Ray &ray) const {
  // TODO: Proper implementation!
  return 0.0;
}
