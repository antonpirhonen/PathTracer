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

void Environment::LoadEnvironment(std::string path) {
    std::ifstream file (path);
    if (!file.is_open()) {
        std::cout << ".obj file " << path <<" not found" << std::endl;
    }

    std::string line;
    std::vector<Vec3> vertices;
    Material material = Material();
    while (std::getline(file, line)) {
        if (line.substr(0, 2)== "v "){
            std::istringstream iss(line.substr(2));
            double x, y, z;
            iss>>x;iss>>y;iss>>z;
            vertices.push_back(Vec3(x,y,z));
        } else if (line.substr(0, 2)== "f ") {
            std::istringstream iss(line.substr(2));
            int i, j, k;
            iss>>i;iss>>j;iss>>k;
            bodies_.push_back(new Triangle(material, vertices.at(i-1), vertices.at(j-1), vertices.at(k-1)));
        }
    }

}