#include "MaterialTransparent.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random.hpp"

#include <iostream>
#include <cmath>

Vec3 MaterialTransparent::Reflect(Vec3 original_direction, Vec3 unit_normal){

    float orig_dot_n = original_direction.DotProduct(unit_normal);
    float sin_orig = std::sqrt(1-std::pow(orig_dot_n,2));
    float ref_angle;
    float n1 = 1.0;
    float n2 = ref_index_;

    if (orig_dot_n > 0 ){
        if(sin_orig > 1/n2){
            Vec3 new_direction = original_direction - 2.0*unit_normal*orig_dot_n;  
            new_direction.Normalize();
            return new_direction;
        }
        else{
            n1 = ref_index_;
            n2 = 1.0;
        }
    }
    //Snell
    float sin_refrac = n1/n2 * sin_orig;

    //Fresnell
    float orig_angle = std::asin(sin_orig);
    float refrac_angle = std::asin(sin_refrac);
    float rpar = std::tan(orig_angle-refrac_angle)/std::tan(orig_angle+refrac_angle);
    float rperp = std::sin(orig_angle-refrac_angle)/std::sin(orig_angle+refrac_angle);
    float r = (std::pow(rpar,2) + std::pow(rperp,2))/2;

    if(Random::randomNumber() < r){
        Vec3 new_direction = original_direction - 2.0*unit_normal*orig_dot_n;  
        new_direction.Normalize();
        return new_direction;       
    }

    Vec3 new_direction = n1/n2*original_direction+(n1/n2*cos(orig_angle)-std::sqrt(1-std::pow(sin_refrac,2)))*unit_normal;
    new_direction.Normalize();

    return new_direction;
}
