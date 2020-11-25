#ifndef BODY_HPP
#define BODY_HPP
#include "Vec3.hpp"
#include "structs.hpp"
#include "Ray.hpp"
#include <utility>
#include <tuple>
#include <vector>
#include "Material.hpp"


// Abstract base class for environment objects.
class Body {

public:
  Body(Material* material) : material_(material) { }
  const Material* GetMaterial() const;
  virtual std::tuple<float, float, float> FindCollision(Ray &ray) const = 0;
  virtual void Reflect(Ray &ray, Vec3 &new_origin, float, float) = 0;

protected:
  Material* material_;

};

#endif