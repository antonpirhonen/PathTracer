#ifndef RAY_HPP
#define RAY_HPP
#include <array>
#include "structs.hpp"

class Ray {
public:
    Ray(Vec3 origin, Vec3 direction, size_t collisions_Left = 10, RGB_color color = RGB_color{0,0,0}, Color_removal color_rem = Color_removal{1,1,1})
        : origin_(origin), direction_(direction), collisions_Left_(collisions_Left), color_(color), color_rem_(color_rem){}

    void SetNewDirection(Vec3);
    void SetNewOrigin(Vec3);
    void SetNewColor(RGB_color);
    void RemoveColor(Color_removal);
    void SetFinished() { finished_ = true; };

    RGB_color GetColor();
    Vec3 GetDirection() {return direction_; };
    Vec3 GetOrigin() {return origin_; };
    
    bool IsFinished() {return finished_; };

private:
    Vec3 origin_;
    Vec3 direction_;
    RGB_color color_ ;
    Color_removal color_rem_;
    size_t collisions_Left_;
    bool finished_ = false;
    int Ceiling(float);
};

#endif
