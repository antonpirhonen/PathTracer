#include <iostream>
#include "Environment.hpp"
#include <vector>
#include "Vec3.hpp"
#include "structs.hpp"
#include "Triangle.hpp"
#include "Ball.hpp"
#include "CameraSimple.hpp"

int main() {
    Environment env = Environment();
    env.PrintInfo();
    Material specular = Material();
    Material radiant = Material(true, RGB_color{255,255,255}); 
//Kertun
//    CameraSimple cam = CameraSimple(Vec3{0,0,3}, Vec3{-2,6,5}, Vec3{2,6,1}, 10, 10);
//    Triangle spec_tr = Triangle(specular, Vec3{-2,12,5}, Vec3{-2, 14,1}, Vec3{2,13,5});
//    Triangle rad_tr = Triangle(radiant, Vec3{0,11,3}, Vec3{0,11,2}, Vec3{1,11,3});
//Sama lähempänä
//    Triangle spec_tr = Triangle(specular, Vec3{-2,7,5}, Vec3{-2, 7,1}, Vec3{2,7,5});
//    Triangle rad_tr = Triangle(radiant, Vec3{0,6,3}, Vec3{0,6,2}, Vec3{1,6,3});
    
//    Triangle rad_tr = Triangle(radiant, Vec3{-2,6,5}, Vec3{2,6,1}, Vec3{2,6,5});
    Triangle spec_tr = Triangle(specular, Vec3{1,-1,1}, Vec3{1,1,1}, Vec3{1,1,-1});
    Triangle rad_tr1 = Triangle(radiant, Vec3{-1,-1,1}, Vec3{1,1,1}, Vec3{1,1,-1});
    Triangle rad_tr2 = Triangle(radiant, Vec3{-1,-1,1}, Vec3{-1,-1,-1}, Vec3{-1,1,-1});
    CameraSimple cam = CameraSimple(Vec3{0,0,0}, Vec3{1,-1,1}, Vec3{1,1,-1}, 10, 10);

    env.AddBody(&spec_tr);
    env.AddBody(&rad_tr1);
    env.AddBody(&rad_tr2);
    env.PrintInfo();

    cam.GetImage(env);
    return 0;
}
