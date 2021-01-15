//
// Created by Ilias Ahmindach on 14/12/2020.
//

#ifndef DUNGEONRUNNER_RANDOM_H
#define DUNGEONRUNNER_RANDOM_H
#include <random>

class Random {
public:

    static Random& getInstance();
    /**
     * generates float
     * @return float 0-1
     */
    static double generateRandomChance();
    /**
     * Generates integer between 0 and max
     * @param max int
     * @return integer between 0 and max
     */
    static int generateRandInt(int max);
    /**
    * Generates integer between min and max
    * @param min int
    * @param max int
    * @return integer between min and max
    */
    static int generateRandInt(int min, int max);
    /**
     * generates float between min and max
     * @param min float
     * @param max float
     * @return float between min and max
     */
    static float generateRandFloat(float min, float max);


private:
    /**
     * Constructor
     */
    Random();
    /**
     * Destructor
     */
    ~Random() = default;
    /**
     * generates float
     * @return float 0-1
     */
    double _generateRandomChance();
    /**
     * Generates integer between 0 and max
     * @param max int
     * @return integer between 0 and max
     */
    int _generateRandomInt(int max);
    /**
     * Generates integer between min and max
     * @param min int
     * @param max int
     * @return integer between min and max
     */
    int _generateRandomInt(int min,int max);
    /**
     * generates float between min and max
     * @param min float
     * @param max float
     * @return float between min and max
     */
    float _generateRandomFloat(float min, float max);
    /**
     * getter for generator
     * @return mt19937 generator (rng)
     */
    std::mt19937 &getGenerator();
    std::random_device rDev;
    std::mt19937 rng;
    std::uniform_real_distribution<> fDist;
};


#endif //DUNGEONRUNNER_RANDOM_H
