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
  Body(Material& material) : material_(&material) { }
  const Material& GetMaterial() const;
  virtual float FindCollision(Ray &ray) const = 0;

private:
  const Material* material_;

};

#endif