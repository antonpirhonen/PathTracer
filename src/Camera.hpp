#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <array>
#include <iostream>

#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "structs.hpp"

class Camera{
public:
    Camera(Path& direction, size_t x_reso = 1000, size_t y_reso = 1000, float x_angle = 45, float y_angle = 45)
    : path_(direction), x_reso_(x_reso), y_reso_(y_reso), x_angle_(x_angle), y_angle_(y_angle) {}

    void GetImage(Environment& env);
    
    void SetAngles(float x, float y);
    void SetDirection(Path& p);

    std::ostream PrintInfo(std::ostream os);

    std::string Time();

private:
    Path& path_;
    const size_t x_reso_;
    const size_t y_reso_; 
    float x_angle_;
    float y_angle_;
};

#endif