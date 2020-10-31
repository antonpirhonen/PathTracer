#include "Body.hpp"
#include <vector>

class Environment {

public:
    Environment();
    std::vector<Body> GetBodies();
    bool AddBody(Body&);
    void PrintInfo();
    void SaveEnvironment(std::string);
    void LoadEnvironment(std::string);
    void LoadBodyFromFile(std::string);

private:
    std::vector<Body> bodies_ = { };
    float x_range [] = { };
    float y_range [] = { };
    float z_range [] = { };
};