#include "Scene.hpp"
#include <filesystem>
#include "Camera.hpp"

Vec3 Scene::ParseVector(json &vector) {
    std::cout << "Parsed vector: " << vector["x"] << ", " << vector["y"] << ", " << vector["z"] << std::endl;
    return Vec3(vector["x"], vector["y"], vector["z"]);
}

Color Scene::ParseColor(json &color) {
    std::cout << "Parsed color: " << color["r"] << ", " << color["g"] << ", " << color["b"] << std::endl;
    return Color(color["r"], color["g"], color["b"]);
}

void Scene::DrawImageFrom(std::string fileName, int samples_per_pixel) {

    std::ifstream file(fileName);
    json scene;
    file >> scene;
    file.close();

    auto cameraInfo = scene["camera"];
    auto focalPoint = ParseVector(cameraInfo["focalPoint"]);
    auto direction = ParseVector(cameraInfo["direction"]);

    Camera parsedCamera = Camera(focalPoint, direction, cameraInfo["xReso"], cameraInfo["yReso"], cameraInfo["xAngle"], cameraInfo["yAngle"]);
    std::cout << "Added camera!" << std::endl;
    Environment sceneEnv = Environment();

    for (auto material : scene["materials"]) {

        if (material["type"] == "specular")
            {
                auto materialColor = ParseColor(material["color"]);
                auto materialColorRem = ParseColor(material["colorRem"]);
                auto materialIsLuminous = material["isLuminous"];
                auto specular = new MaterialSpecular(materialIsLuminous, materialColor, materialColorRem);
                sceneEnv.AddMaterial(specular);
                //std::cout << "Added specular material" << std::endl;

            } else if (material["type"] == "diffuse")
            {
                auto materialColor = ParseColor(material["color"]);
                auto materialColorRem = ParseColor(material["colorRem"]);
                auto materialMattness = material["mattness"];
                auto materialIsLuminous = material["isLuminous"];
                auto diffuse = new MaterialDiffuse(materialIsLuminous, materialColor, materialColorRem, materialMattness);
                sceneEnv.AddMaterial(diffuse);
                //std::cout << "Added diffuse material" << std::endl;

            } else if (material["type"] == "transparent")
            {
                auto materialColor = ParseColor(material["color"]);
                auto materialColorRem = ParseColor(material["colorRem"]);
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
		auto midpoint = ParseVector(object["midpoint"]);
		auto height = object["height"];
		auto xrot = object["xrot"];
		auto yrot = object["yrot"];
		auto zrot = object["zrot"];
                auto objPath = object["path"];
                std::cout << "Added mesh object!, Comment: " << comment << std::endl;

		std::filesystem::path p = fileName;
		std::string meshdir = p.remove_filename().string();
                sceneEnv.LoadMesh(meshdir, objPath, material, midpoint, height, xrot, yrot, zrot);

        } 
    }

    sceneEnv.PrintInfo();
    parsedCamera.GetImage(sceneEnv, samples_per_pixel);
}
