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
    /*
    MaterialDiffuse diffuse = MaterialDiffuse(false, Color(0,0,0), Color(1,0,0), 0.01);
    MaterialDiffuse diffuse2 = MaterialDiffuse(false, Color(0,0,0), Color(0.9,0.9,0.9), 0.01);
    MaterialSpecular specular = MaterialSpecular(false, Color(0,0,0), Color(1,1,0));
    MaterialSpecular radiant = MaterialSpecular(true, Color(1,1,1));
    MaterialTransparent transparent = MaterialTransparent(false, Color(0,0,0), Color(1,0,0), 2);
    //Kaksi yksinkertaista testiä
    //Ensimmäinen
    //    Triangle spec_tr = Triangle(specular, Vec3(1,-1,1), Vec3(1,1,-1), Vec3(1,1,1));
    //    Triangle rad_tr1 = Triangle(radiant, Vec3(-1,-1,1), Vec3(1,1,1), Vec3(1,1,-1));
    //    Triangle rad_tr2 = Triangle(radiant, Vec3(-1,-1,1), Vec3(-1,-1,-1), Vec3(-1,1,-1));
    //    CameraSimple cam = CameraSimple(Vec3(0,0,0), Vec3(1,-1,1), Vec3(1,1,-1), 10, 10);
    //Toinen
    CameraSimple cam = CameraSimple(Vec3(0,0,0), Vec3(4,-2,2), Vec3(4,2,-2), 1000, 1000);
    Triangle spec_tr = Triangle(diffuse, Vec3(4,-2,2), Vec3(6,-2,-3), Vec3(6,3,2));
    Triangle rad_tr = Triangle(radiant, Vec3(4,1,-1), Vec3(4,1,0), Vec3(4,0,-1));
    Triangle trans_tr = Triangle(transparent, Vec3(0,1,-1), Vec3(4,1,0), Vec3(4,0,-1));

    //    env.AddBody(&rad_tr);
    env.AddBody(&spec_tr);
    env.AddBody(&rad_tr);
    Triangle background = Triangle(diffuse2, Vec3(40,-2,2), Vec3(60,-2,-3), Vec3(60,3,2));
    env.AddBody(&background);
    //    env.AddBody(&rad_tr2);
    */
    Environment env = Environment();
    CameraSimple cam = CameraSimple(Vec3(-7,0,0), Vec3(4,-2,2), Vec3(4,2,-2), 100, 100);

    MaterialSpecular radiant = MaterialSpecular(true, Color(1,1,1));
    Triangle rad_tr = Triangle(radiant, Vec3(-8,200,-200), Vec3(-8,200,0), Vec3(-8,0,-200));
    Triangle rad_tr2 = Triangle(radiant, Vec3(-8,-200,200), Vec3(-8,200,0), Vec3(-8,0,-200));
    env.AddBody(rad_tr);
    env.AddBody(rad_tr2);
    auto material = MaterialDiffuse(false, Color(0,0,0), Color(1,0,0), 0.3);
    env.LoadEnvironment("./sphere.obj", material);
    env.PrintInfo();

    cam.GetImage(env,15);
    return 0;
}
