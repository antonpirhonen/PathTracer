#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Body.hpp"
#include "Triangle.hpp"
#include "Material.hpp"
#include <vector>

class Environment {

public:
    Environment();
    ~Environment();
    std::vector<Triangle>& GetBodies();
    void AddBody(Triangle&);
    void AddMaterial(Material*);
    Material* MaterialAt(int);
    void PrintInfo() const;
    void LoadMesh(std::string path, Material* material,
		  Vec3 midpoint, float height,
		  float xrot, float yrot, float zrot);

private:
    std::vector<Material*> materials_ = { };
    std::vector<Triangle> bodies_ = { };
    std::pair<float, float> x_range_;
    std::pair<float, float> y_range_;
    std::pair<float, float> z_range_;
};

#endif
