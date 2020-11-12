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
    color_ = ncolor;
    std::cout << "red " << ncolor.red_;   
    std::cout << " blue " << ncolor.blue_;
    std::cout << " green " << ncolor.green_ <<  std::endl;
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
//    std::cout << "red " << color_.red_ << " rem " << color_rem_.red_ << std::endl;   
    size_t r = Ceiling(color_.red_ * color_rem_.red_);
//    std::cout << "blue " << color_.blue_ << " rem " << color_rem_.blue_ << std::endl;
    size_t g = Ceiling(color_.green_ * color_rem_.green_); 
//    std::cout << "green " << color_.green_ << " rem " << color_rem_.green_ << std::endl;
    size_t b = Ceiling(color_.blue_ * color_rem_.blue_);
    RGB_color color = RGB_color{r,g,b};
//    std::cout << "GetColor\n";
//    std::cout << "red " << color.red_;   
//    std::cout << " blue " << color.blue_;
//    std::cout << " green " << color.green_ <<  std::endl;
    return RGB_color{r,g,b};
}

