#ifndef SPECULAR_HPP
#define SPECULAR_HPP

#include "structs.hpp"
#include "Material.hpp"

class MaterialSpecular : public Material {
public:
    MaterialSpecular(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1)) :
	Material(luminous, color, color_rem) { };

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);
    
private:

};

#endif