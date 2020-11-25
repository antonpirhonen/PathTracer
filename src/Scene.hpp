#ifndef SCENE_HPP
#define SCENE_HPP

#include "JSON.hpp"
#include <iostream>
#include <fstream>

#include "Vec3.hpp"
#include "Color.hpp"
#include "CameraSimple.hpp"
#include "Environment.hpp"

#include "MaterialSpecular.hpp"
#include "MaterialDiffuse.hpp"
#include "MaterialTransparent.hpp"

#include "Triangle.hpp"

using json = nlohmann::json;

class Scene {
public:
    Scene() {
    }

    void parseScene(std::string fileName);

private:
    Vec3 parseVector(json &vector);
    Color parseColor(json &color);

};

#endif