#include "Environment.hpp"
#include "Triangle.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "Vec3.hpp"
#include "MaterialSpecular.hpp"

Environment::Environment() { }
Environment::~Environment() {
    for (auto material : materials_) {
        delete material;
    }
}

std::vector<Triangle>& Environment::GetBodies() {
    return bodies_;
}

void Environment::AddBody(Triangle& body) {
    bodies_.push_back(body);
}

void Environment::AddMaterial(Material* material) {
    materials_.push_back(material);
}

Material* Environment::MaterialAt(int i) {
    return materials_.at(i);
}

void Environment::PrintInfo() const {
    std::cout << bodies_.size() << " Bodies" << std::endl;
}

static int Count(std::string str, char c) {
    int count = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == c) count++;
    }
    return count;
}

static std::vector<std::string> Split(std::string str, char c) {
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
    parts.push_back(current);

    return parts;
}

static std::tuple<Vec3, Vec3> BoundingBox(std::vector<Triangle>& triangles) {
    float l = std::numeric_limits<float>::lowest();
    float h = std::numeric_limits<float>::max();
    float mincoords[] = { h, h, h };
    float maxcoords[] = { l, l, l };

    for (auto t : triangles) {
	std::tuple<Vec3, Vec3, Vec3> vertices = t.GetVertices();
	Vec3 v0 = std::get<0>(vertices);
	Vec3 v1 = std::get<1>(vertices);
	Vec3 v2 = std::get<2>(vertices);
	mincoords[0] = (mincoords[0] < v0.X()) ? mincoords[0] : v0.X();
	mincoords[0] = (mincoords[0] < v1.X()) ? mincoords[0] : v1.X();
	mincoords[0] = (mincoords[0] < v2.X()) ? mincoords[0] : v2.X();
	mincoords[1] = (mincoords[1] < v0.Y()) ? mincoords[1] : v0.Y();
	mincoords[1] = (mincoords[1] < v1.Y()) ? mincoords[1] : v1.Y();
	mincoords[1] = (mincoords[1] < v2.Y()) ? mincoords[1] : v2.Y();
	mincoords[2] = (mincoords[2] < v0.Z()) ? mincoords[2] : v0.Z();
	mincoords[2] = (mincoords[2] < v1.Z()) ? mincoords[2] : v1.Z();
	mincoords[2] = (mincoords[2] < v2.Z()) ? mincoords[2] : v2.Z();

	maxcoords[0] = (maxcoords[0] > v0.X()) ? maxcoords[0] : v0.X();
	maxcoords[0] = (maxcoords[0] > v1.X()) ? maxcoords[0] : v1.X();
	maxcoords[0] = (maxcoords[0] > v2.X()) ? maxcoords[0] : v2.X();
	maxcoords[1] = (maxcoords[1] > v0.Y()) ? maxcoords[1] : v0.Y();
	maxcoords[1] = (maxcoords[1] > v1.Y()) ? maxcoords[1] : v1.Y();
	maxcoords[1] = (maxcoords[1] > v2.Y()) ? maxcoords[1] : v2.Y();
	maxcoords[2] = (maxcoords[2] > v0.Z()) ? maxcoords[2] : v0.Z();
	maxcoords[2] = (maxcoords[2] > v1.Z()) ? maxcoords[2] : v1.Z();
	maxcoords[2] = (maxcoords[2] > v2.Z()) ? maxcoords[2] : v2.Z();
    }
    return std::make_tuple(Vec3(mincoords[0], mincoords[1], mincoords[2]),
			   Vec3(maxcoords[0], maxcoords[1], maxcoords[2]));
}

void Environment::LoadMesh(std::string path, Material* material,
			   Vec3 midpoint, float height,
			   float xrot, float yrot, float zrot) {
    std::ifstream file (path);
    if (!file.is_open()) {
        std::cout << ".obj file " << path <<" not found" << std::endl;
        return;
    }

    std::string line;
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Triangle> triangles;
    //MaterialSpecular material = MaterialSpecular(true, Color(1,1,1));
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
            int slashCount = Count(a, '/');
            if (slashCount == 2) {
                auto parts_a = Split(a, '/');
                auto parts_b = Split(b, '/');
                auto parts_c = Split(c, '/');
                Triangle tr = Triangle(material,
                    vertices.at(std::stoi(parts_a.at(0))-1),
                    vertices.at(std::stoi(parts_b.at(0))-1),
                    vertices.at(std::stoi(parts_c.at(0))-1),
                    normals.at(std::stoi(parts_a.at(2))-1),
                    normals.at(std::stoi(parts_b.at(2))-1),
                    normals.at(std::stoi(parts_c.at(2))-1));
                triangles.push_back(tr);
            } else if (slashCount == 0) {
                Triangle tr = Triangle(material,
                    vertices.at(std::stoi(a)-1),
                    vertices.at(std::stoi(b)-1),
                    vertices.at(std::stoi(c)-1));
                triangles.push_back(tr);
            }
        } else if ((line.substr(0, 2)== "vn")) {
            std::istringstream iss(line.substr(2));
            float x, y, z;
            iss>>x;iss>>y;iss>>z;
            Vec3 v = Vec3(x,y,z);
            v.Normalize();
            normals.push_back(v);
        }
    }

    // Rotate:
    for (auto &tr : triangles) {
	tr.RotateAroundXAxisBy(xrot);
	tr.RotateAroundYAxisBy(yrot);
	tr.RotateAroundZAxisBy(zrot);
    }
    // Move to origin:
    std::tuple<Vec3, Vec3> bb = BoundingBox(triangles);
    Vec3 mid = (std::get<0>(bb) + std::get<1>(bb));
    mid = mid / 2;
    Vec3 d = mid.Reverse();
    for (auto &tr : triangles) {
	tr.MoveBy(d);
    }
    // Scale:
    float current_height = (std::get<1>(bb) - std::get<0>(bb)).Z();
    float ratio = height / current_height;
    for (auto &tr : triangles) {
	tr.ScaleBy(ratio);
    }
    // Move away from origin:
    for (auto &tr : triangles) {
	tr.MoveBy(midpoint);
    }
    // Append to bodies_:
    bodies_.insert(bodies_.end(), triangles.begin(), triangles.end());
}
