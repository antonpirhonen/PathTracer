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
#include "Scene.hpp"

int main() {
    
    Scene scene = Scene();
    scene.parseScene("./scene.json");
    
    return 0;
}
