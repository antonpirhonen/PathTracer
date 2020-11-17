#include "Ray.hpp"
#include "structs.hpp"

void Ray::SetNewDirection(Vec3 dir){
    direction_ = dir;
}

void Ray::SetNewOrigin(Vec3 orig){
    origin_ = orig;
}

void Ray::SetNewColor(Color ncolor){
  color_ = ncolor;
}

void Ray::RemoveColor(Color k){
  color_= color_ * k;
}

Color Ray::GetColor(){
  return color_;
}

