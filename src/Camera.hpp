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
    Camera(Vec3 origin, Vec3 direction, size_t x_reso, size_t y_reso, float x_angle, float y_angle);

    void GetImage(Environment& env, unsigned int spp);

private:
    Vec3 direction_;
    Vec3 origin_;
    const size_t x_reso_;
    const size_t y_reso_; 
    float x_angle_;
    float y_angle_;
};

#endif
