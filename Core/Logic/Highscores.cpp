//
// Created by Ilias Ahmindach on 23/12/2020.
//

#include "Highscores.h"


DungeonRunner::Highscores::Highscores(const std::string& fileName): fileName(fileName) {
    loadHighscores(fileName);
}

void DungeonRunner::Highscores::loadHighscores(std::string fileName) {
    std::ifstream highscoreFile(fileName);
    std::string hs;
    while(std::getline(highscoreFile, hs)){ // Reads text file line per line
        std::string hsName = hs.substr(0,hs.find(' '));
        std::string hsScore = hs.substr(hs.find(' '),hs.size());
        highScores[hsName].insert(std::stoi(hsScore));
    }
}

void DungeonRunner::Highscores::writeToFile() {
    std::ofstream wFile(fileName,std::ofstream::out | std::ofstream::trunc); // Flushes file and re-inserts every highscore into file
    for(auto &hs:highScores){
        for(auto &playerScore:hs.second) {
            wFile << hs.first << " " << playerScore <<"\n";
        }
    }
}

void DungeonRunner::Highscores::addScore(const std::string scoreName, int score) {
    highScores[scoreName].insert(score);
}

