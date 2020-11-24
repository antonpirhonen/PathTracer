#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP
#include "structs.hpp"
#include "Material.hpp"

class MaterialDiffuse : public Material {
public:
    MaterialDiffuse(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1), float mattness = 1) :
	Material(luminous, color, color_rem), mattness_(mattness)  { };

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);
    
private:
    float mattness_;
};

#endif