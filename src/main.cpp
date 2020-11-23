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
#include "MaterialTransparent.hpp"
#include "Color.hpp"

int main() {
    Environment env = Environment();
    env.PrintInfo();
    MaterialDiffuse diffuse = MaterialDiffuse(false, Color(0,0,0), Color(1,0,0), 1);
    MaterialSpecular specular = MaterialSpecular(false, Color(0,0,0), Color(1,1,0));
    MaterialSpecular radiant = MaterialSpecular(true, Color(1,1,1)); 
    MaterialTransparent transparent = MaterialTransparent(false, Color(0,0,0), Color(1,0,1), 2);

    CameraSimple cam = CameraSimple(Vec3{0,0,0}, Vec3{-4,-10,10}, Vec3{-4,10,-10}, 1000, 1000);

/*
    //Kaksi yksinkertaista testiä
    //Ensimmäinen
    //    Triangle spec_tr = Triangle(specular, Vec3(1,-1,1), Vec3(1,1,-1), Vec3(1,1,1));
    //    Triangle rad_tr1 = Triangle(radiant, Vec3(-1,-1,1), Vec3(1,1,1), Vec3(1,1,-1));
    //    Triangle rad_tr2 = Triangle(radiant, Vec3(-1,-1,1), Vec3(-1,-1,-1), Vec3(-1,1,-1));
    //    CameraSimple cam = CameraSimple(Vec3(0,0,0), Vec3(1,-1,1), Vec3(1,1,-1), 10, 10);
    //Toinen

    Triangle spec_tr = Triangle(diffuse, Vec3{-4,-2,2}, Vec3{-6,-2,-3}, Vec3{-6,3,2});
//    Triangle rad_tr = Triangle(radiant, Vec3{4,2,-2}, Vec3{4,2,2}, Vec3{4,-2,-2});
    Triangle trans_tr = Triangle(transparent, Vec3{1,1,0}, Vec3{-3,0,-1}, Vec3{-3,1,-1});

    //    env.AddBody(&rad_tr);
//    env.AddBody(&spec_tr);
//    env.AddBody(&rad_tr);
//    env.AddBody(&trans_tr);
//    env.AddBody(&rad_tr2);
    env.PrintInfo();
*/

// Tests for transparent material
//    Triangle rad_tr = Triangle(radiant, Vec3{-5,-1.25,-0.75}, Vec3{-5,0.75,1.25}, Vec3{-5,0.75,-0.75});
    Triangle rad_tr = Triangle(radiant, Vec3{-5, 10,-10}, Vec3{-5, 10, 10}, Vec3{-5, -10, -10});
    Triangle ikkuna = Triangle(transparent, Vec3{-4, 10,-10}, Vec3{-4, -10, -10}, Vec3{-4, 10, 10});
//    Triangle trans_tr_pois = Triangle(transparent, Vec3{3.5,1,-1}, Vec3{3,-1,-1}, Vec3{4,1,1});
//    Triangle trans_tr_pain = Triangle(transparent, Vec3{3,1,-1}, Vec3{3.5,1,1}, Vec3{2.5,-1,-1});
//    Triangle trans_tr_suora = Triangle(transparent, Vec3{-2, 0.75, -0.75}, Vec3{-5,0.75,1.25}, Vec3{-5,0.75,-0.75});

    env.AddBody(&rad_tr);
//    env.AddBody(&trans_tr_pois);
//    env.AddBody(&trans_tr_pain);
    env.AddBody(&ikkuna);

    cam.GetImage(env,100);
    return 0;
}
