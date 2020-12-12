#include <iostream>
#include "Core/Game.h"
#include "Core/Representation/World.h"
int main()
{
    std::shared_ptr<sf::RenderWindow> gWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(2048,2048),"Test");
    gWindow->setFramerateLimit(60);
    gWindow->clear();
    auto *newGame = new DungeonRunner::Game(gWindow);
    while (gWindow->isOpen()){
        gWindow->clear();
        newGame->update();
        gWindow->display();
    }

    return 0;
}