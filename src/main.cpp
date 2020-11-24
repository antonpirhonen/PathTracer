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
    CameraSimple cam = CameraSimple(Vec3(-7,0,0), Vec3(4,-2,2), Vec3(4,2,-2), 200, 200);

    MaterialSpecular radiant = MaterialSpecular(true, Color(1,1,1));
    Triangle rad_tr = Triangle(radiant, Vec3(-8,200,-200), Vec3(-8,200,0), Vec3(-8,0,-200));
    Triangle rad_tr2 = Triangle(radiant, Vec3(-8,-200,200), Vec3(-8,200,0), Vec3(-8,0,-200));
    env.AddBody(rad_tr);
    env.AddBody(rad_tr2);
    auto material = MaterialDiffuse(false, Color(0,0,0), Color(1,0,0), 0.1);
    env.LoadEnvironment("./sphere.obj", material);
    env.PrintInfo();

    cam.GetImage(env,3);
    return 0;
}
