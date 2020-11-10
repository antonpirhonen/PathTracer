#include "Environment.hpp"
#include "Triangle.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Vec3.hpp"

Environment::Environment() { }

std::vector<Body*> const Environment::GetBodies() const {
    return bodies_;
}

void Environment::AddBody(Body* body) {
    bodies_.push_back(body);
}

void Environment::PrintInfo() const {
    std::cout << bodies_.size() << " Bodies" << std::endl;
}

int Count(std::string str, char c) {
    int count = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == c) count++;
    }
    return count;
}

std::vector<std::string> Split(std::string str, char c) {
    std::vector<std::string> parts;
    size_t count = 0;
    std::string current = "";
    while (count < str.size()) {
        if (str[count] != c) {
            current.push_back(str[count]);
        } else {
            parts.push_back(current);
            current = "";
        }
        count++;
    }

    return parts;
}

void Environment::LoadEnvironment(std::string path) {
    std::ifstream file (path);
    if (!file.is_open()) {
        std::cout << ".obj file " << path <<" not found" << std::endl;
        return;
    }

    std::string line;
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    Material material = Material();
    while (std::getline(file, line)) {
        if (line.substr(0, 2)== "v "){
            std::istringstream iss(line.substr(2));
            float x, y, z;
            iss>>x;iss>>y;iss>>z;
            vertices.push_back(Vec3(x,y,z));
        } else if (line.substr(0, 2)== "f ") {
            std::istringstream iss(line.substr(2));
            std::string a, b, c;
            iss>>a;iss>>b;iss>>c;
            std::cout << "A: " << a << ", B: " << b << ", C: " << c << std::endl;
            int slashCount = Count(a, '/');
            if (slashCount == 2) {
                auto parts_a = Split(a, '/');
                auto parts_b = Split(b, '/');
                auto parts_c = Split(c, '/');
                bodies_.push_back(new Triangle(material,
                    vertices.at(std::stoi(parts_a[0])-1),
                    vertices.at(std::stoi(parts_b[0])-1),
                    vertices.at(std::stoi(parts_c[0])-1)));
            } else if (slashCount == 0) {
                bodies_.push_back(new Triangle(material,
                    vertices.at(std::stoi(a)-1),
                    vertices.at(std::stoi(b)-1),
                    vertices.at(std::stoi(c)-1)));
            }
        } else if ((line.substr(0, 2)== "vn")) {
            std::istringstream iss(line.substr(2));
            float x, y, z;
            iss>>x;iss>>y;iss>>z;
            normals.push_back(Vec3(x,y,z));
        }
    }

}