#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Vec3.hpp"

namespace Random {

    // returns random number thats in [0, 1)
    float randomNumber() {
        static std::mt19937 generator(std::time(0));
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

    // returns random number thats in [min, max)
    float randomNumber(float min, float max) {
        static std::mt19937 generator(std::time(0));
        static std::uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }

    // returns random vector where X, Y, Z each are random numbers in [0, 1)
    Vec3 RandomVector() {
        return Vec3(randomNumber(), randomNumber(), randomNumber());
    }

    // returns random vector where X, Y, Z each are random numbers in [min, max)
    Vec3 RandomVector(float min, float max) {
        return Vec3(randomNumber(min, max), randomNumber(min, max), randomNumber(min, max));
    }

    //returns random vector atmost "degree" degrees away from given vector "vector"
    Vec3 RandomVector(Vec3 vector, float degree) {

        auto angle = degree * M_PI / 180.0;
        auto phi_lower = M_PI - angle;
        auto theta = 2 * M_PI * randomNumber();
        auto phi = acos(1 - (cos(phi_lower) + 1) * randomNumber());
        Vec3 randomVector = Vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));

        auto a1 = atan2(sqrt(vector.X() * vector.X() + vector.Y() * vector.Y()), vector.Z());
        auto a2 = atan2(vector.Y(), vector.X());

        double R[3][3] = {(cos(a1) * cos(a2), -sin(a2), sin(a1) * cos(a2)),
                        (cos(a1) * sin(a2), cos(a2), sin(a1) * sin(a2)),
                        (-sin(a1), 0, cos(a1))};

        return Vec3((randomVector.X() * R[0][0] + randomVector.Y() * R[1][0] + randomVector.Z() * R[2][0]),
                    (randomVector.X() * R[0][1] + randomVector.Y() * R[1][1] + randomVector.Z() * R[2][1]),
                    (randomVector.X() * R[0][2] + randomVector.Y() * R[1][2] + randomVector.Z() * R[2][2]));

    }

    //returns random vector from unit sphere
    Vec3 RandomVectorInUnitSpehere() {

        auto theta = 2 * M_PI * randomNumber();
        auto phi = acos(1 - 2 * randomNumber());
        return Vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
        
    }

    //returns random vector from same hemispehere with given "normal" vector
    Vec3 RandomVectorInHemisphere(Vec3 normal) {

        Vec3 vector = RandomVectorInUnitSpehere();

        if (normal.DotProduct(vector) > 0.0)
        {
            return vector;
        } else {
            return -1.0 * vector;
        }
        

    }

}

#endif