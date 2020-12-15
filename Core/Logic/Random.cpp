//
// Created by Ilias Ahmindach on 14/12/2020.
//

#include "Random.h"

double Random::generateRandomChance() {
    return getInstance()._generateRandomChance();
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

Random::Random(){
    rng.seed(rDev());
}

Random &Random::getInstance() {
    static Random newInstance;
    return newInstance;
}

double Random::_generateRandomChance() {
    if(fDist.min() == 0 and fDist.max() == 1)  return fDist(getInstance().getGenerator());
    fDist = std::uniform_real_distribution<>(0,1);
    return fDist(getInstance().getGenerator());

}

std::mt19937 &Random::getGenerator() {
    return rng;
}


