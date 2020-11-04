#include <iostream>
#include "Environment.hpp"
#include <vector>
#include "Vec3.hpp"
#include "structs.hpp"
#include "Triangle.hpp"
#include "Ball.hpp"

int main() {
    auto environment = Environment();
    environment.PrintInfo();
    auto material = Material();
    auto tr = Triangle(material, Vec3(3,4,8), Vec3(6,8,8), Vec3(3,4,8));
    auto sphere = Ball(material, Vec3(12,4,8), 2);
    environment.AddBody(&tr);
    environment.AddBody(&sphere);
    environment.PrintInfo();

    return 0;
}