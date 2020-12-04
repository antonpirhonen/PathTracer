#ifndef TRANSPARENT_HPP
#define TRANSPARENT_HPP
#include "structs.hpp"
#include "Material.hpp"

class MaterialTransparent : public Material {
public:
    MaterialTransparent(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1), float ref_index = 1) :
        Material(luminous, color, color_rem), ref_index_(ref_index)  { };

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);

    float GetR(float cos);
    
private:
    float ref_index_;
};

#endif
