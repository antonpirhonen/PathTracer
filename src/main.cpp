#include <iostream>
#include "Environment.hpp"
#include <vector>
#include "Vec3.hpp"
#include "structs.hpp"
#include "Triangle.hpp"
#include "Ball.hpp"
#include "CameraSimple.hpp"
#include "MaterialSpecular.hpp"
#include "MaterialDiffuse.hpp"

int main() {
    Environment env = Environment();
    env.PrintInfo();
    MaterialDiffuse diffuse = MaterialDiffuse(false, RGB_color{0,0,0}, Color_removal{1,0,0}, 0.01);
    MaterialSpecular specular = MaterialSpecular(false, RGB_color{0,0,0}, Color_removal{1,0,0});
    MaterialSpecular radiant = MaterialSpecular(true, RGB_color{255,255,255}); 

    //Kaksi yksinkertaista testiä
    //Ensimmäinen
//    Triangle spec_tr = Triangle(specular, Vec3{1,-1,1}, Vec3{1,1,-1}, Vec3{1,1,1});
//    Triangle rad_tr1 = Triangle(radiant, Vec3{-1,-1,1}, Vec3{1,1,1}, Vec3{1,1,-1});
//    Triangle rad_tr2 = Triangle(radiant, Vec3{-1,-1,1}, Vec3{-1,-1,-1}, Vec3{-1,1,-1});
//    CameraSimple cam = CameraSimple(Vec3{0,0,0}, Vec3{1,-1,1}, Vec3{1,1,-1}, 10, 10);
    //Toinen
    CameraSimple cam = CameraSimple(Vec3{0,0,0}, Vec3{4,-2,2}, Vec3{4,2,-2}, 1000, 1000);
    Triangle spec_tr = Triangle(diffuse, Vec3{4,-2,2}, Vec3{6,-2,-3}, Vec3{6,3,2});
    Triangle rad_tr = Triangle(radiant, Vec3{4,1,-1}, Vec3{4,1,0}, Vec3{4,0,-1});

//    env.AddBody(&rad_tr);
    env.AddBody(&spec_tr);
    env.AddBody(&rad_tr);
//    env.AddBody(&rad_tr2);
    env.PrintInfo();

    cam.GetImage(env);
    return 0;
}
