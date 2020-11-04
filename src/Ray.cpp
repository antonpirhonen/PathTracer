#include "Ray.hpp"
#include "structs.hpp"

void Ray::SetNewPath(Path& npath){
    path_ = npath;
}

void Ray::SetNewColor(RGB_color& ncolor){
    color_ = ncolor;
}

void Ray::RemoveColor(std::array<float,3> k){
    color_rem_= {k[0]*color_rem_[0], k[1]*color_rem_[1], k[2]*color_rem_[2]};
}

int Ray::Ceiling(float n) {
    int m = (int)n;
    if (n == m) {
        return m;
    }
    return m + 1;
}

RGB_color Ray::GetColor(){
    size_t r = Ceiling(color_.red_ * color_rem_[0]);
    size_t g = Ceiling(color_.green_ * color_rem_[1]);
    size_t b = Ceiling(color_.blue_ * color_rem_[2]);

    return RGB_color{r, g, b};
}
