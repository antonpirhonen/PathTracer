#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP
#include "Material.hpp"
#include "Vec3.hpp"

class MaterialDiffuse : public Material {
public:
    MaterialDiffuse(bool luminous, Color color, Color color_rem, float mattness);

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