#include "MaterialDiffuse.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random.hpp"
#include <iostream>

MaterialDiffuse::MaterialDiffuse(bool luminous = false, Color color = Color(0,0,0), Color color_rem = Color(1,1,1), float mattness = 1) :
	Material(luminous, color, color_rem), mattness_(mattness)  
    { 
        if(mattness < 0) mattness_ = -mattness;
        if(mattness > 1) mattness_ = 1;
    }


Vec3 MaterialDiffuse::Reflect(Vec3 original_direction, Vec3 unit_normal){
    
    float dot_product = original_direction.DotProduct(unit_normal);
    Vec3 new_direction = original_direction - 2.0*unit_normal*dot_product;
    Vec3 rand_direction;
    bool flag = true;
    
    rand_direction = Random::RandomVector(new_direction, 90*mattness_);
    float rand_dot_n = rand_direction.DotProduct(unit_normal);
    
    if(rand_dot_n*dot_product > 0) {
	float dot2 = rand_direction.DotProduct(unit_normal);
	rand_direction = rand_direction - 2.0*unit_normal*dot2;
    }
    
    return rand_direction;
}
