#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"
#include "Vec3.hpp"

class Material {
public:
    Material(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1)) :
	luminous_(luminous), color_(color) , color_rem_(color_rem) { };
    bool GetLuminosity() const { return luminous_; };
    Color GetColor() const { return color_; };
    const Color GetColorRem() const { return color_rem_; };
    virtual Vec3 Reflect(Vec3, Vec3) = 0;

protected:
    bool luminous_;
    Color color_;
    Color color_rem_;
};

#endif
