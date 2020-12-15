#include <iostream>
#include "Core/Game.h"
#include "Core/Representation/World.h"
#include "Core/Logic/Transformation.h"
#include <random>
int main()
{
//    std::shared_ptr<sf::RenderWindow> gWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024,1024),"Test",sf::Style::Titlebar|sf::Style::Close);
//    gWindow->setFramerateLimit(60);
//    gWindow->clear();
//    auto *newGame = new DungeonRunner::Game(gWindow);
//    while (gWindow->isOpen()){
//        gWindow->clear();
//        newGame->update();
//        gWindow->display();
//    }
    std::cout <<Random::generateRandomChance();
    return 0;
}