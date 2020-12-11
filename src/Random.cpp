#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Vec3.hpp"
#include "Random.hpp"

    // returns random number thats in [0, 1)
float Random::randomNumber() {
    thread_local std::mt19937 generator(std::time(0));
    thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

    // returns random number thats in [min, max)
float Random::randomNumber(float min, float max) {
    thread_local std::mt19937 generator(std::time(0));
    thread_local std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

    // returns random vector where X, Y, Z each are random numbers in [0, 1)
Vec3 Random::RandomVector() {
    return Vec3(randomNumber(), randomNumber(), randomNumber());
}

    // returns random vector where X, Y, Z each are random numbers in [min, max)
Vec3 Random::RandomVector(float min, float max) {
    return Vec3(randomNumber(min, max), randomNumber(min, max), randomNumber(min, max));
}

    //returns random vector atmost "degree" degrees away from given vector "vector"
Vec3 Random::RandomVector(Vec3 vector, float degree) {

    auto angle = degree * M_PI / 180.0;
    auto phi_lower = M_PI - angle;
    auto theta = 2 * M_PI * randomNumber();
    auto phi = acos(1 - (cos(phi_lower) + 1) * randomNumber());
    Vec3 randomVector = Vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));

    auto a1 = atan2(sqrt(vector.X() * vector.X() + vector.Y() * vector.Y()), vector.Z());
    auto a2 = atan2(vector.Y(), vector.X());

    randomVector = randomVector.RotateAroundYAxis(a1 * 180 / M_PI);
    randomVector = randomVector.RotateAroundZAxis(a2 * 180 / M_PI);

    return randomVector;

}

    //returns random vector from unit sphere
Vec3 Random::RandomVectorInUnitSpehere() {

    auto theta = 2 * M_PI * randomNumber();
    auto phi = acos(1 - 2 * randomNumber());
    return Vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
        
}

    //returns random vector from same hemispehere with given "normal" vector
Vec3 Random::RandomVectorInHemisphere(Vec3 normal) {

    Vec3 vector = RandomVectorInUnitSpehere();

    if (normal.DotProduct(vector) > 0.0)
    {
    return vector;
    } else {
    return -1.0 * vector;
    }
}
