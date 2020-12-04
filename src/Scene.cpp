#include "Scene.hpp"
#include "Camera.hpp"
#include <filesystem>
#include <stdexcept> 

Vec3 Scene::ParseVector(json &vector) {
    // std::cout << "Parsed vector: " << vector["x"] << ", " << vector["y"] << ", " << vector["z"] << std::endl;
    return Vec3(vector["x"], vector["y"], vector["z"]);
}

Color Scene::ParseColor(json &color) {
    // std::cout << "Parsed color: " << color["r"] << ", " << color["g"] << ", " << color["b"] << std::endl;
    return Color(color["r"], color["g"], color["b"]);
}

void Scene::DrawImageFrom(std::string fileName, int samples_per_pixel) {

    std::ifstream file(fileName);
    if (!file) {
        throw std::invalid_argument("JSON file with given path not found.");
    }

    json scene;
    file >> scene;
    file.close();
    auto cameraInfo = scene["camera"];
    auto focalPoint = ParseVector(cameraInfo["focalPoint"]);
    auto direction = ParseVector(cameraInfo["direction"]);

    Camera parsedCamera = Camera(focalPoint, direction, cameraInfo["xReso"], cameraInfo["yReso"], cameraInfo["xAngle"], cameraInfo["yAngle"]);
    Environment sceneEnv = Environment();

    auto materials = scene["materials"];
    if (materials.size() == 0) throw std::invalid_argument("No materials defined in JSON.");

    for (auto material : materials) {
        auto materialColor = ParseColor(material["color"]);
        auto luminosity = material["isLuminous"];

        if (luminosity) {
            auto lightSource = new MaterialSpecular(luminosity, materialColor);
            sceneEnv.AddMaterial(lightSource);
            continue;
        }

        if (material["type"] == "specular") {
            auto specular = new MaterialSpecular(luminosity, Color(0,0,0), materialColor);
            sceneEnv.AddMaterial(specular);
            continue;
        }
        
        if (material["type"] == "diffuse") {
            auto materialMattness = material["mattness"];
            auto diffuse = new MaterialDiffuse(luminosity, Color(0,0,0), materialColor, materialMattness);
            sceneEnv.AddMaterial(diffuse);
            continue;
        }
        
        if (material["type"] == "transparent") {
            auto materialRefIndex = material["refIndex"];
            auto transparent = new MaterialTransparent(luminosity, Color(0,0,0), materialColor, materialRefIndex);
            sceneEnv.AddMaterial(transparent);
        }
    }

    for (auto object : scene["objects"]) {
        if (object["type"] == "mesh") {
            auto comment = object["comment"];
            auto materialIndex = object["materialIndex"];
            auto material = sceneEnv.MaterialAt(materialIndex);
            auto midpoint = ParseVector(object["midpoint"]);
            auto height = object["height"];
            auto xrot = object["xrot"];
            auto yrot = object["yrot"];
            auto zrot = object["zrot"];
            auto objPath = object["path"];

            std::filesystem::path p = fileName;
            std::string meshdir = p.remove_filename().string();
            sceneEnv.LoadMesh(meshdir, objPath, material, midpoint, height, xrot, yrot, zrot);
        }
    }

    sceneEnv.PrintInfo();
    parsedCamera.GetImage(sceneEnv, samples_per_pixel);
}
