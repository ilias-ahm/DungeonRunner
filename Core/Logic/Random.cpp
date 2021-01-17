//
// Created by Ilias Ahmindach on 14/12/2020.
//

#include "Random.h"

double Random::generateRandomChance() { return getInstance()._generateRandomChance(); }

int Random::generateRandInt(int min, int max) { return getInstance()._generateRandomInt(min, max); }

int Random::generateRandInt(int max) { return getInstance()._generateRandomInt(max); }

Random::Random() { rng.seed(rDev()); }

Random& Random::getInstance()
{
        static Random newInstance;
        return newInstance;
}

double Random::_generateRandomChance()
{
        if (fDist.min() == 0 and fDist.max() == 1)
                return fDist(getInstance().getGenerator());
        fDist = std::uniform_real_distribution<>(0, 1);
        return fDist(getInstance().getGenerator());
}

std::mt19937& Random::getGenerator() { return rng; }

int Random::_generateRandomInt(int max)
{
        std::uniform_int_distribution<int> iDist(0, max);
        return iDist(getInstance().getGenerator());
}

int Random::_generateRandomInt(int min, int max)
{
        std::uniform_int_distribution<int> iDist(min, max);
        return iDist(getInstance().getGenerator());
}

float Random::_generateRandomFloat(float min, float max)
{
        fDist = std::uniform_real_distribution<>(min, max);
        return fDist(getInstance().getGenerator());
}

float Random::generateRandFloat(float min, float max) { return getInstance()._generateRandomFloat(min, max); }
