#include <iostream>
#include "Environment.hpp"
#include <vector>
#include "Vec3.hpp"
#include "structs.hpp"

int main() {
    auto environment = Environment();
    environment.PrintInfo();

    auto tr = Triangle(
        std::make_tuple(Vec3(3,4,8), Vec3(6,8,8), Vec3(3,4,8)),
        1.0, Vec3(1,1,1), 1.0, RGB_color{1,1,1}
    );
    auto sphere = Ball(
        Vec3(12,4,8), 2, 1, Vec3(1,1,1), 1.0, RGB_color{1,1,1}
    );

    environment.AddBody(&tr);
    environment.AddBody(&sphere);
    environment.PrintInfo();

    return 0;
}