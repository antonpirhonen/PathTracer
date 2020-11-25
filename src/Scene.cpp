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

    for (auto light : scene["lights"]) {

        if  (light["type"] == "triangle") {

            Color lightColor = parseColor(light["color"]);

            auto radiant = MaterialSpecular(true, lightColor);

            auto vertices = light["vertices"];

            auto vertice1 = parseVector(vertices["1"]);
            auto vertice2 = parseVector(vertices["2"]);
            auto vertice3 = parseVector(vertices["3"]);

            auto light = Triangle(radiant, vertice1, vertice2, vertice3);

            std::cout << "Added light!" << std::endl;

            sceneEnv.AddBody(light);
        }

    }

    for (auto object : scene["objects"]) {

        if (object["type"] == "triangle") {

            auto material = object["material"];

            // Liikaa toistoa?? Saisiko jotenkin vähennettyä??
            
            if (material["type"] == "specular")
            {

                auto materialColor = parseColor(material["color"]);

                auto materialColorRem = parseColor(material["colorRem"]);

                auto specular = MaterialSpecular(false, materialColor, materialColorRem);

                auto vertices = object["vertices"];

                auto obj = Triangle(specular, parseVector(vertices["1"]), parseVector(vertices["2"]), parseVector(vertices["3"]));

                std::cout << "Added specular triangle!" << std::endl;

                sceneEnv.AddBody(obj);

            } else if (material["type"] == "diffuse")
            {
                
                auto materialColor = parseColor(material["color"]);

                auto materialColorRem = parseColor(material["colorRem"]);

                auto materialMattness = material["mattness"];

                auto diffuse = MaterialDiffuse(false, materialColor, materialColorRem, materialMattness);

                auto vertices = object["vertices"];

                auto obj = Triangle(diffuse, parseVector(vertices["1"]), parseVector(vertices["2"]), parseVector(vertices["3"]));

                std::cout << "Added diffuse triangle!" << std::endl;

                sceneEnv.AddBody(obj);

            } else if (material["type"] == "transparent")
            {
                
                auto materialColor = parseColor(material["color"]);

                auto materialColorRem = parseColor(material["colorRem"]);

                auto materialRefIndex = material["refIndex"];

                auto transparent = MaterialTransparent(false, materialColor, materialColorRem, materialRefIndex);

                auto vertices = object["vertices"];

                auto obj = Triangle(transparent, parseVector(vertices["1"]), parseVector(vertices["2"]), parseVector(vertices["3"]));

                std::cout << "Added transparent triangle!" << std::endl;

                sceneEnv.AddBody(obj);

            }           

        } else if (object["type"] == "mesh") {

            auto material = object["material"];

            // Liikaa toistoa?? Saisiko jotenkin vähennettyä??
            
            if (material["type"] == "specular")
            {

                auto materialColor = parseColor(material["color"]);

                auto materialColorRem = parseColor(material["colorRem"]);

                auto specular = MaterialSpecular(false, materialColor, materialColorRem);

                auto objPath = object["path"]; 

                std::cout << "Added specular mesh!" << std::endl;

                sceneEnv.LoadEnvironment(objPath, specular);

            } else if (material["type"] == "diffuse")
            {
                
                auto materialColor = parseColor(material["color"]);

                auto materialColorRem = parseColor(material["colorRem"]);

                auto materialMattness = material["mattness"];

                MaterialDiffuse diffuse = MaterialDiffuse(false, materialColor, materialColorRem, materialMattness);

                auto objPath = object["path"]; 

                std::cout << "Added diffuse mesh!" << std::endl;

                sceneEnv.LoadEnvironment(objPath, diffuse);

            } else if (material["type"] == "transparent")
            {
                
                auto materialColor = parseColor(material["color"]);

                auto materialColorRem = parseColor(material["colorRem"]);

                auto materialRefIndex = material["refIndex"];

                auto transparent = MaterialTransparent(false, materialColor, materialColorRem, materialRefIndex);

                auto objPath = object["path"]; 

                std::cout << "Added transparent mesh!" << std::endl;

                sceneEnv.LoadEnvironment(objPath, transparent);

            }

        }

    }

    sceneEnv.PrintInfo();

    parsedCamera.GetImage(sceneEnv, 10);

}