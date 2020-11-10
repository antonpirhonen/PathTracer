#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Vec3.hpp"

float randomNumber() {
    static std::mt19937 generator(std::time(0));
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}


float randomNumber(float min, float max) {
    static std::mt19937 generator(std::time(0));
    static std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

Vec3 RandomVector() {
    return Vec3(randomNumber(), randomNumber(), randomNumber());
}

Vec3 RandomVector(float min, float max) {
    return Vec3(randomNumber(min, max), randomNumber(min, max), randomNumber(min, max));
}

Vec3 RandomVectorInXDegreeFromOther(Vec3 vector, double degree) {

    Vec3 givenVector = vector;
    givenVector.Normalize();

    while (true) {

        Vec3 randomNormalVector = RandomVector(-1, 1);

        randomNormalVector.Normalize();
        
        if (acos(randomNormalVector.DotProduct(givenVector)) * 180 / M_PI < degree) continue;
        return randomNormalVector;

    }

}

Vec3 RandomVectorInUnitSpehere() {

    while (true) {
        Vec3 vector = RandomVector(-1,1);
        if (vector.DotProduct(vector) >= 1) continue;
        return vector;
    }
    
}

Vec3 RandomVectorInHemisphere(Vec3 normal) {

    Vec3 vector = RandomVectorInUnitSpehere();

    if (normal.DotProduct(vector) > 0.0)
    {
        return vector;
    } else {
        return -1.0 * vector;
    }
    

}

#endif