#include "MaterialSpecular.hpp"
#include "Material.hpp"
#include "Vec3.hpp"


Vec3 MaterialSpecular::Reflect(Vec3 original_direction, Vec3 unit_normal){
    
    float dot_product = original_direction.DotProduct(unit_normal);
    Vec3 new_direction = original_direction - 2.0*unit_normal*dot_product;  
    new_direction.Normalize();

    return new_direction;
}