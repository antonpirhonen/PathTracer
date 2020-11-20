#ifndef TRANSPARENT_HPP
#define TRANSPARENT_HPP
#include "structs.hpp"
#include "Material.hpp"

class MaterialTransparent : public Material {
public:
    MaterialTransparent(bool luminous = false, RGB_color color = RGB_color{0,0,0}, Color_removal color_rem = Color_removal{1,1,1}, float ref_index = 1) :
        Material(luminous, color, color_rem), ref_index_(ref_index)  { };

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);
    
private:
    float ref_index_;
};

#endif