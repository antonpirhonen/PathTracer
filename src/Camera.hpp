#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <omp.h>

#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Image.hpp"

class Camera {
public:
    Camera(Vec3 origin, Vec3 direction, size_t x_reso = 1000, size_t y_reso = 1000, float x_angle = 45, float y_angle = 45)
    : origin_(origin),direction_(direction),  x_reso_(x_reso), y_reso_(y_reso), x_angle_(x_angle), y_angle_(y_angle) {}

    void GetImage(Environment& env, unsigned int spp);
    
    void SetAngles(float x, float y);
    void SetDirection(Path& p);

    std::ostream PrintInfo(std::ostream os);

    std::string Time();

private:
    Vec3 direction_;
    Vec3 origin_;
    const size_t x_reso_;
    const size_t y_reso_; 
    float x_angle_;
    float y_angle_;
};

#endif
