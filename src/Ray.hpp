#ifndef RAY_HPP
#define RAY_HPP
#include <array>
#include "structs.hpp"
#include "Color.hpp"

class Ray {
public:
  Ray(Vec3 origin = Vec3{0,0,0}, Vec3 direction = Vec3{0,0,0},
      size_t collisions_Left = 10, Color color = Color(1,1,1))
    : origin_(origin), direction_(direction), collisions_Left_(collisions_Left),
      color_(color) { }
  
  void SetNewDirection(Vec3);
  void SetNewOrigin(Vec3);
  void SetNewColor(Color);
  void RemoveColor(Color);
  void SetFinished() { finished_ = true; };

  Color GetColor();
  Vec3 GetDirection() {return direction_; };
  Vec3 GetOrigin() {return origin_; };
    
  bool IsFinished() {return finished_; };

private:
  Vec3 origin_;
  Vec3 direction_;
  Color color_ ;
  size_t collisions_Left_;
  bool finished_ = false;
};

#endif
