#include "Ray.hpp"
#include "structs.hpp"
#include "iostream"

void Ray::SetNewDirection(Vec3 dir){
    this -> direction_ = dir;
}

void Ray::SetNewOrigin(Vec3 orig){
    this -> origin_ = orig;
}

void Ray::SetNewColor(RGB_color ncolor){
    this -> color_ = ncolor;
}

void Ray::RemoveColor(Color_removal k){
    this -> color_rem_= {k.red_*color_rem_.red_, k.green_*color_rem_.green_, k.blue_*color_rem_.blue_};
}

int Ray::Ceiling(float n) {
    int m = (int)n;
    if (n == m) {
        return m;
    }
    return m + 1;
}

RGB_color Ray::GetColor(){
    std::cout << "red " << color_.red_ << " rem " << color_rem_.red_ << std::endl;   
    size_t r = Ceiling(color_.red_ * color_rem_.red_);
    std::cout << "blue " << color_.blue_ << " rem " << color_rem_.blue_ << std::endl;
    size_t g = Ceiling(color_.green_ * color_rem_.green_); 
    std::cout << "green " << color_.green_ << " rem " << color_rem_.green_ << std::endl;
    size_t b = Ceiling(color_.blue_ * color_rem_.blue_);
    return RGB_color{r, g, b};
}

