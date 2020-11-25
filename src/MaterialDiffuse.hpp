#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP
#include "structs.hpp"
#include "Material.hpp"

class MaterialDiffuse : public Material {
public:
    MaterialDiffuse(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1), float mattness = 1) :
	Material(luminous, color, color_rem), mattness_(mattness)  { };

    MaterialDiffuse(MaterialDiffuse& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
        mattness_ = m.mattness_;
    }
    MaterialDiffuse(const MaterialDiffuse& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
        mattness_ = m.mattness_;
    }
    MaterialDiffuse operator=(MaterialDiffuse& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
        mattness_ = m.mattness_;
        return *this;
    }
    MaterialDiffuse operator=(const MaterialDiffuse& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
        mattness_ = m.mattness_;
        return *this;
    }

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);
    
private:
    float mattness_;
};

#endif