#include "Triangle.hpp"

Triangle::Triangle(Material& material, std::tuple<Vec3, Vec3, Vec3> vertices) :
  Body(material), vertices_(vertices) {
  Vec3 normal = (std::get<1>(vertices) -
		 std::get<0>(vertices)).CrossProduct(std::get<2>(vertices) -
						     std::get<0>(vertices));
  normal.Normalize();
  unit_normal_ = normal;
}

float Triangle::FindCollision(Ray &ray) const {
  // TODO: Proper implementation!
  return 0.0;
}
