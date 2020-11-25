#include "Scene.hpp"

Vec3 Scene::parseVector(json &vector) {
    std::cout << "Parsed vector: " << vector["x"] << ", " << vector["y"] << ", " << vector["z"] << std::endl;
    return Vec3(vector["x"], vector["y"], vector["z"]);
}

Color Scene::parseColor(json &color) {
    std::cout << "Parsed color: " << color["r"] << ", " << color["g"] << ", " << color["b"] << std::endl;
    return Color(color["r"], color["g"], color["b"]);
}

void Scene::parseScene(std::string fileName) {

    std::ifstream file(fileName);
    json scene;
    file >> scene;
    file.close();

    auto cameraInfo = scene["camera"];
    auto focalPoint = parseVector(cameraInfo["focalPoint"]);
    auto tlCorner = parseVector(cameraInfo["tlCorner"]);
    auto brCorner = parseVector(cameraInfo["brCorner"]);

    CameraSimple parsedCamera = CameraSimple(focalPoint, tlCorner, brCorner, cameraInfo["xReso"], cameraInfo["yReso"]);
    std::cout << "Added camera!" << std::endl;
    Environment sceneEnv = Environment();

    for (auto material : scene["materials"]) {

        if (material["type"] == "specular")
            {
                auto materialColor = parseColor(material["color"]);
                auto materialColorRem = parseColor(material["colorRem"]);
                auto materialIsLuminous = material["isLuminous"];
                auto specular = new MaterialSpecular(materialIsLuminous, materialColor, materialColorRem);
                sceneEnv.AddMaterial(specular);
                //std::cout << "Added specular material" << std::endl;

            } else if (material["type"] == "diffuse")
            {
                auto materialColor = parseColor(material["color"]);
                auto materialColorRem = parseColor(material["colorRem"]);
                auto materialMattness = material["mattness"];
                auto materialIsLuminous = material["isLuminous"];
                auto diffuse = new MaterialDiffuse(materialIsLuminous, materialColor, materialColorRem, materialMattness);
                sceneEnv.AddMaterial(diffuse);
                //std::cout << "Added diffuse material" << std::endl;

            } else if (material["type"] == "transparent")
            {
                auto materialColor = parseColor(material["color"]);
                auto materialColorRem = parseColor(material["colorRem"]);
                auto materialRefIndex = material["refIndex"];
                auto materialIsLuminous = material["isLuminous"];
                auto transparent = new MaterialTransparent(materialIsLuminous, materialColor, materialColorRem, materialRefIndex);
                sceneEnv.AddMaterial(transparent);
                //std::cout << "Added transparent material" << std::endl;

            } 
    }

for (auto object : scene["objects"]) {

        if (object["type"] == "mesh") {
                auto comment = object["comment"];
                auto materialIndex = object["materialIndex"];
                auto material = sceneEnv.MaterialAt(materialIndex);
                auto objPath = object["path"]; 
                std::cout << "Added mesh object!, Comment: " << comment << std::endl;
                sceneEnv.LoadEnvironment(objPath, material);
        } 
    }

    sceneEnv.PrintInfo();
    parsedCamera.GetImage(sceneEnv, 1);
}