//
// Created by Ilias Ahmindach on 14/12/2020.
//

#include "Random.h"

double Random::generateRandomChance() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dist(0,1); // distribution in range [1, 6]
    return dist(rng);
}

int Random::generateRandInt(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0,1); // distribution in range [1, 6]
    return dist(rng);
}

int Random::generateRandInt(int max) {
    return 0;
}

Random::Random() {
    rng = std::mt19937(rDev());
}

Random &Random::getInstance() {
    return Random();
}
