#include "MaterialTransparent.hpp"
#include "Material.hpp"
#include "Vec3.hpp"

Vec3 MaterialTransparent::Reflect(Vec3 original_direction, Vec3 unit_normal){
    return original_direction;
}