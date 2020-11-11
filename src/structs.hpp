#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <array>
#include "Vec3.hpp"

struct Path
{
    Vec3 location_;
    Vec3 direction_;
};

struct RGB_color
{
    size_t red_;
    size_t green_;
    size_t blue_;
};

struct Color_removal
{
    float red_;
    float green_;
    float blue_;
};

#endif
