#ifndef SPECULAR_HPP
#define SPECULAR_HPP

#include "Material.hpp"
#include "Vec3.hpp"

class MaterialSpecular : public Material {
public:
    MaterialSpecular(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1)) :
	Material(luminous, color, color_rem) { };

    MaterialSpecular(MaterialSpecular& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
    }
    
    MaterialSpecular(const MaterialSpecular& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
    }

    MaterialSpecular operator=(MaterialSpecular& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
        return *this;
    }

    MaterialSpecular operator=(const MaterialSpecular& m) {
        luminous_ = m.luminous_;
        color_ = m.color_;
        color_rem_ = m.color_rem_;
        return *this;
    }

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);
    
private:

};

#endif