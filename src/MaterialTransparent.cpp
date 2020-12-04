#ifndef TRANSPARENT_CPP
#define TRANSPARENT_CPP

#include "MaterialTransparent.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random.hpp"

#include <iostream>
#include <cmath>

Vec3 MaterialTransparent::Reflect(Vec3 original_direction, Vec3 unit_normal){

    //tarkista tuleeko säde sisältä vai ulkoa
    //lasketaan tulokulma normaaliin nähden pistetulosta dot_product
    //sisältä tullessa tarkistetaan kokonaisheijastumisen kulma sin(tulokulma) > 1/refraktiivinen indeksi 
    //jos kokonaisheijastus, reflektoidaan kuten speculaari (1. return)
    //Snellin laki antaa mahdollisen taittuneen kulman
    //Fresnelin yhtälöistä rs ja rp -> heijastumisen prosenttiosuus F_r = (rs^2 + rp^2)/2
    //heijastumisen todennäköisyys -> arvotaan taittuuko vai heijastuuko säde
    //Jos heijastuu, reflektoidaan kuten speculaari (2. return)
    //jos taittuu:
    //ks uusi suunta = sin(lähtökulma)/sin(tulokulma)*(original_direction - dot_product*unit_normal) + dot_product*unit_normal


    /*float orig_dot_n = original_direction.DotProduct(unit_normal);
    float sin_orig = std::sqrt(1-std::pow(orig_dot_n,2));
    float ref_angle;
    float n1 = 1.0;
    float n2 = ref_index_;

    if (orig_dot_n > 0.f ){
        outward_normal = -unit_normal
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
    return new_direction;*/

    float orig_dot_n = original_direction.DotProduct(unit_normal);
    Vec3 outward_normal;
    Vec3 reflected = (original_direction - 2.0*unit_normal*orig_dot_n);
    reflected.Normalize();
    Vec3 refracted;
    float cos;
    float n;
    float r;


    if(orig_dot_n > 0.f){
        outward_normal = unit_normal.Reverse();
        n = ref_index_;
        cos = std::sqrt(1.f - n*n *(1 -orig_dot_n*orig_dot_n));
    }else{
        outward_normal = unit_normal;
        n = 1/ref_index_;
        cos = -orig_dot_n;
    }
    

    float orig_dot_out = original_direction.DotProduct(outward_normal);
    float discriminant = 1.f - n*n *(1.f -orig_dot_out*orig_dot_out);
    
    if (discriminant > 0.f){
        refracted = n*original_direction - unit_normal*(std::sqrt(discriminant) + n*orig_dot_out);
        r = GetR(cos);
    }else{
        r = 1;
    }

    if(Random::randomNumber() < r){
        return reflected;
    }
    else{
        return refracted;
    }

}

float MaterialTransparent::GetR(float cos){
    float r0 = (1.f - ref_index_)/(1.f + ref_index_);
    r0 = r0*r0;
    float diff = 1.f - cos;
    r0 = r0 + (1.f - r0)*std::pow(diff,5);
    return r0;
}

#endif

    //Vec3 new_direction = (original_direction - orig_dot_n*unit_normal)*tan(refrac_angle)/tan(orig_angle) + orig_dot_n*unit_normal;
