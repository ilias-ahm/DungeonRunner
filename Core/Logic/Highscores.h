//
// Created by Ilias Ahmindach on 23/12/2020.
//

#ifndef DUNGEONRUNNER_HIGHSCORES_H
#define DUNGEONRUNNER_HIGHSCORES_H
#include <iostream>
#include <fstream>
#include <map>
#include <set>
namespace DungeonRunner {
    class Highscores {
        std::map<std::string,std::set<int>> highScores; // Map with playernames and all their scores
        std::string fileName;
    public:
        /**
         * Constructor
         * @param fileName
         */
        Highscores(const std::string& fileName);
        /**
         * Loads highscores from a txt file
         * @param fileName
         */
        void loadHighscores(std::string fileName);
        /**
         * Writes to the selected txt file
         */
        void writeToFile();
        /**
         * adds new score to highscores
         * @param scoreName name of scoreholder
         * @param score highscore
         */
        void addScore(std::string scoreName, int score);
    };
}


#endif //DUNGEONRUNNER_HIGHSCORES_H
