#include "Ball.hpp"
#include <limits>
#include <cmath>

Ball::Ball(Material& material, Vec3 center, float radius) :
  Body(material), center_(center), radius_(radius) { }

float Ball::FindCollision(Ray& ray) const {
  Vec3 lc = ray.GetPath().location_ - center_;
  float a = ray.GetPath().direction_.DotProduct(ray.GetPath().direction_);
  float b = 2.0 * lc.DotProduct(ray.GetPath().direction_);
  float c = lc.DotProduct(lc);

  float discriminant = b*b - 4*a*c;
  if (discriminant < 0)
    return std::numeric_limits<float>::infinity();
  else
    return (-b - sqrt(discriminant)) / (2.0*a);
}

