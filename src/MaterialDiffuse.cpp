#include "MaterialDiffuse.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random"

Vec3 MaterialDiffuse::Reflect(Vec3 original_direction, Vec3 unit_normal){
    
    float dot_product = original_direction.DotProduct(unit_normal);
    Vec3 new_direction = original_direction - 2.0*unit_normal*dot_product;
    Vec3 rand_direction;
    bool flag = true;
    while (flag){
        rand_direction = Random::RandomVector(new_direction);
        
        float rand_dot_n = new_direction.DotProduct(unit_normal);
        if(rand_dot_n > 0){
            flag = false;
        }
    }

    rand_direction.Normalize();
    return rand_direction;
}