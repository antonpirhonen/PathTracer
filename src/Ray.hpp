#pragma once
#include <array>
#include "structs.hpp"

class Ray {
public:
    Ray(Path& path, size_t collisions_Left, RGB_color& color, std::array<float,3> color_rem = {1,1,1})
        : path_(path), collisions_Left_(collisions_Left), color_(color), color_rem_(color_rem){}

    void SetNewPath(Path&);
    void SetNewColor(RGB_color&);
    void RemoveColor(std::array<float,3>);

    RGB_color GetColor();

    bool IsFinished() {return finished_;};

private:
    Path& path_;
    RGB_color& color_ ;
    std::array<float,3> color_rem_;
    size_t collisions_Left_;
    bool finished_ = false;
};