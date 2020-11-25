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

    // read a JSON file
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
    std::vector<MaterialSpecular> materials = { };

    for (auto material : scene["materials"]) {

        if (material["type"] == "specular")
            {
                auto materialColor = parseColor(material["color"]);
                auto materialColorRem = parseColor(material["colorRem"]);
                auto materialIsLuminous = material["isLuminous"];
                auto specular = MaterialSpecular(materialIsLuminous, materialColor, materialColorRem);
                materials.push_back(specular);
                auto m = materials.back();
                std::cout << "Is Luminous: " << (m.GetLuminosity() ? "true" : "false") << std::endl;
                auto c = m.GetColor();
                auto cr = m.GetColorRem();
                std::cout << c;
                std::cout << "Color Removal" << cr;

            } else if (material["type"] == "diffuse")
            {
                auto materialColor = parseColor(material["color"]);
                auto materialColorRem = parseColor(material["colorRem"]);
                auto materialMattness = material["mattness"];
                auto materialIsLuminous = material["isLuminous"];
                auto diffuse = MaterialDiffuse(materialIsLuminous, materialColor, materialColorRem, materialMattness);
                //lisää materiaali

            } else if (material["type"] == "transparent")
            {
                auto materialColor = parseColor(material["color"]);
                auto materialColorRem = parseColor(material["colorRem"]);
                auto materialRefIndex = material["refIndex"];
                auto materialIsLuminous = material["isLuminous"];
                auto transparent = MaterialTransparent(materialIsLuminous, materialColor, materialColorRem, materialRefIndex);

                // lisää materiaali

            } 

    }

for (auto object : scene["objects"]) {

        if (object["type"] == "triangle") {

                auto comment = object["comment"];

                auto vertices = object["vertices"];

                auto materialIndex = object["materialIndex"];

                // hae materiaali materialIndexistä
                // auto material = ???

                // luo kolmio
                //auto obj = Triangle(material, parseVector(vertices["1"]), parseVector(vertices["2"]), parseVector(vertices["3"]));

                //lisää kolmio
                //sceneEnv.AddBody(obj);

                std::cout << "Added triangle shaped object!, Comment: " << comment << std::endl;           

        } else if (object["type"] == "mesh") {

                
                auto comment = object["comment"];

                auto materialIndex = object["materialIndex"];

                // hae materiaali materialIndexistä
                auto material = materials.at(materialIndex);

                auto objPath = object["path"]; 

                std::cout << "Added mesh object!, Comment: " << comment << std::endl;

                //lataa .obj 
                sceneEnv.LoadEnvironment(objPath, material);

        } 

    }

    sceneEnv.PrintInfo();
    // for (auto tr : sceneEnv.GetBodies()) {
    //     std::cout << "Is Luminous: " << (tr.GetMaterial().GetLuminosity() ? "true" : "false") << std::endl;
    //     auto c = tr.GetMaterial().GetColor();
    //     auto cr = tr.GetMaterial().GetColorRem();
    //     std::cout << c;
    //     std::cout << "Color Removal" << cr;
    // }

    parsedCamera.GetImage(sceneEnv, 1);

}