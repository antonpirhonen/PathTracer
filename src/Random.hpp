#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Vec3.hpp"

namespace Random {

    // returns random number thats in [0, 1)
    float randomNumber();

    // returns random number thats in [min, max)
    float randomNumber(float min, float max);

    // returns random vector where X, Y, Z each are random numbers in [0, 1)
    Vec3 RandomVector();

    // returns random vector where X, Y, Z each are random numbers in [min, max)
    Vec3 RandomVector(float min, float max);

    //returns random vector atmost "degree" degrees away from given vector "vector"
    Vec3 RandomVector(Vec3 vector, float degree);

    //returns random vector from unit sphere
    Vec3 RandomVectorInUnitSpehere();

    //returns random vector from same hemispehere with given "normal" vector
    Vec3 RandomVectorInHemisphere(Vec3 normal);
}

#endif