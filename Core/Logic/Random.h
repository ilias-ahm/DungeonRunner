//
// Created by Ilias Ahmindach on 14/12/2020.
//

#ifndef DUNGEONRUNNER_RANDOM_H
#define DUNGEONRUNNER_RANDOM_H
#include <random>

class Random {
public:

    static Random& getInstance();
    static double generateRandomChance();
    static int generateRandInt(int min, int max);
    static int generateRandInt(int max);


private:
    Random();
    ~Random() = default;
    double _generateRandomChance();
    int _generateRandomInt(int max);
    int _generateRandomInt(int min,int max);
    std::mt19937 &getGenerator();
    std::random_device rDev;
    std::mt19937 rng;
    std::uniform_real_distribution<> fDist;
};


#endif //DUNGEONRUNNER_RANDOM_H
