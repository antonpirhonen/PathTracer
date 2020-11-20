#ifndef DIFFUSE_CPP
#define DIFFUSE_CPP

#include "MaterialDiffuse.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random.hpp"
#include <iostream>

Vec3 MaterialDiffuse::Reflect(Vec3 original_direction, Vec3 unit_normal){
    
//    std::cout << "Diffuse " << std::endl;
    float dot_product = original_direction.DotProduct(unit_normal);
    Vec3 new_direction = original_direction - 2.0*unit_normal*dot_product;
    Vec3 rand_direction;
    bool flag = true;
    float original_dot_n = original_direction.DotProduct(unit_normal);

    while (flag){
        rand_direction = Random::RandomVector(new_direction, 90*mattness_);
        float rand_dot_n = new_direction.DotProduct(unit_normal);
        if(rand_dot_n*original_dot_n < 0){
            flag = false;
        }
    }

    rand_direction.Normalize();
    return rand_direction;
}

#endif