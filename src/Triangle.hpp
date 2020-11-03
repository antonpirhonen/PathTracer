#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Body.hpp"

class Triangle : public Body {

public:
  Triangle(Material& material, std::tuple<Vec3, Vec3, Vec3> vertices);
  float FindCollision(Ray &ray) const;

private:
  std::tuple<Vec3, Vec3, Vec3> vertices_;
  Vec3 unit_normal_;
};

#endif
