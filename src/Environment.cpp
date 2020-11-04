#include "Environment.hpp"
#include <iostream>
#include <fstream>

Environment::Environment() { }

std::vector<Body*> const Environment::GetBodies() const {
    return bodies_;
}

void Environment::AddBody(Body* body) {
    bodies_.push_back(body);
}

void Environment::PrintInfo() const {
    std::cout << bodies_.size() << " Bodies" << std::endl;
    // for (auto body : bodies_) {
    //     std::cout << body << std::endl;
    // }
}

void Environment::LoadEnvironment(std::string path) {
    std::ifstream istream(path);
    while (!istream.eof()) {
        std::string line;
        std::getline(istream, line);
        std::cout << line << std::endl;
    }
}