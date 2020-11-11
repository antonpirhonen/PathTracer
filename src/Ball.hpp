#ifndef BALL_HPP
#define BALL_HPP

#include "Body.hpp"

class Ball : public Body {

public:
  Ball(Material& material, Vec3 center, float radius);
  float FindCollision(Ray &ray) const;
  void Reflect(Ray &ray, Vec3 &new_origin);

private:
  Vec3 center_;
  float radius_;
  
};


#endif
