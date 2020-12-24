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
        std::map<std::string,std::set<int>> highScores;
        std::string fileName;
    public:
        Highscores(const std::string& fileName);
        void loadHighscores(std::string fileName);
        void writeToFile();
        void addScore(std::string scoreName, int score);
    };
}


#endif //DUNGEONRUNNER_HIGHSCORES_H
