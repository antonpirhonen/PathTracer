#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <array>
#include <iostream>

#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "structs.hpp"

//a Camera is created with a defined resolution, can't be changed
//is now constructed e.g. Camera<10000>(direction, x_reso, y_reso, x_angle, y_angle)
//This is not robust, must be addressed in main function.
//template < int N_RAYS > 

class CameraSimple{
public:
    CameraSimple(Vec3 focal_point, Vec3 tl_corner, Vec3 br_corner, size_t x_reso = 100, size_t y_reso = 100)
    : focal_point_(focal_point), tl_corner_(tl_corner), br_corner_(br_corner), x_reso_(x_reso), y_reso_(y_reso) {}

    void GetImage(Environment& env);
    
    void SetAngles(float x, float y);
    void SetDirection(Path& p);

    std::ostream PrintInfo(std::ostream os);

    std::string Time();

private:
    size_t x_reso_;
    size_t y_reso_; 
    Vec3 focal_point_;
    Vec3 tl_corner_;
    Vec3 br_corner_;
};

#endif