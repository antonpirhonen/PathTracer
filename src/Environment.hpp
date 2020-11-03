#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Body.hpp"
#include <vector>

class Environment {

public:
    Environment();
    std::vector<Body> const GetBodies() const;
    void AddBody(const Body&);
    void PrintInfo() const;
    void SaveEnvironment(std::string);
    void LoadEnvironment(std::string);
    void LoadBodyFromFile(std::string);

private:
    std::vector<Body> bodies_ = { };
    std::pair<float, float> x_range_;
    std::pair<float, float> y_range_;
    std::pair<float, float> z_range_;
};

#endif