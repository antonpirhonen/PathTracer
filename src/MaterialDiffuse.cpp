#ifndef DIFFUSE_CPP
#define DIFFUSE_CPP

#include "MaterialDiffuse.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random.hpp"
#include <iostream>

Vec3 MaterialDiffuse::Reflect(Vec3 original_direction, Vec3 unit_normal){
    
    float dot_product = original_direction.DotProduct(unit_normal);
    Vec3 new_direction = original_direction - 2.0*unit_normal*dot_product;
    Vec3 rand_direction;
    bool flag = true;

    // This has a tendency to get stuck in an infinite loop.
    // Fixed by just reflecting the vector about the plane.
    // This is a little chewing-gumey fix, but it works okay and
    // increases efficiency.
    /*
    while (flag) {
        rand_direction = Random::RandomVector(new_direction, 90*mattness_);
        float rand_dot_n = rand_direction.DotProduct(unit_normal);
        if(rand_dot_n*dot_product < 0){
            flag = false;
        }
    }
    */
    
    rand_direction = Random::RandomVector(new_direction, 90*mattness_);
    float rand_dot_n = rand_direction.DotProduct(unit_normal);
    
    if(rand_dot_n*dot_product > 0) {
	float dot2 = rand_direction.DotProduct(unit_normal);
	rand_direction = rand_direction - 2.0*unit_normal*dot2;
    }
    
    return rand_direction;
}

#endif
