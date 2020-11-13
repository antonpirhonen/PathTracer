#include "Ray.hpp"
#include "structs.hpp"
#include "iostream"

void Ray::SetNewDirection(Vec3 dir){
    direction_ = dir;
}

void Ray::SetNewOrigin(Vec3 orig){
    origin_ = orig;
}

void Ray::SetNewColor(RGB_color ncolor){
    color_ = {ncolor.red_, ncolor.green_, ncolor.blue_};
}

void Ray::RemoveColor(Color_removal k){
    color_rem_= {k.red_*color_rem_.red_, k.green_*color_rem_.green_, k.blue_*color_rem_.blue_};
}

int Ray::Ceiling(float n) {
    int m = (int)n;
    if (n == m) {
        return m;
    }
    return m + 1;
}

RGB_color Ray::GetColor(){
    size_t r = Ceiling(color_.red_ * color_rem_.red_);
    size_t g = Ceiling(color_.green_ * color_rem_.green_); 
    size_t b = Ceiling(color_.blue_ * color_rem_.blue_);
    RGB_color color = RGB_color{r,g,b};
    return RGB_color{r,g,b};
}

