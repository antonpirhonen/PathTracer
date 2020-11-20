#ifndef TRANSPARENT_CPP
#define TRANSPARENT_CPP

#include "MaterialTransparent.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "Random.hpp"

#include <iostream>
#include <cmath>

Vec3 MaterialTransparent::Reflect(Vec3 original_direction, Vec3 unit_normal){
//    std::cout << "TRANSPARENT" << std::endl; 
    //tarkista tuleeko säde sisältä vai ulkoa ok
    //lasketaan tulokulma normaaliin nähden pistetulosta dot_product ok
    //sisältä tullessa tarkistetaan kokonaisheijastumisen kulma sin(tulokulma) > 1/refraktiivinen indeksi 
    //jos kokonaisheijastus, reflektoidaan kuten speculaari (1. return)
    //Snellin laki antaa mahdollisen taittuneen kulman
    //Fresnelin yhtälöistä rs ja rp -> heijastumisen prosenttiosuus F_r = (rs^2 + rp^2)/2
    //heijastumisen todennäköisyys -> arvotaan taittuuko vai heijastuuko säde
    //Jos heijastuu, reflektoidaan kuten speculaari (2. return)
    //jos taittuu:
    //ks uusi suunta = sin(lähtökulma)/sin(tulokulma)*(original_direction - dot_product*unit_normal) + dot_product*unit_normal

    float orig_dot_n = original_direction.DotProduct(unit_normal);
    float sin_orig = std::sqrt(1-std::pow(orig_dot_n,2));
    float ref_angle;
    float n1 = 1.0;
    float n2 = ref_index_;

    if (orig_dot_n > 0 ){
        n1 = ref_index_;
        n2 = 1.0;
        if(sin_orig > 1/n2){
            Vec3 new_direction = original_direction - 2.0*unit_normal*orig_dot_n;  
            new_direction.Normalize();
//            std::cout << "Kokonaisheijastuminen " << sin_orig << std::endl;
            return new_direction;
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
//        std::cout << "Heijastuu " << std::endl;
        return new_direction;       
    }

    Vec3 new_direction = sin_refrac/sin_orig *(original_direction - orig_dot_n*unit_normal) + orig_dot_n*unit_normal;
    new_direction.Normalize();

//    std::cout << "Taittuu " << std::endl;
    return new_direction;

}

#endif