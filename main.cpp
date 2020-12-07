#include <iostream>
#include "Core/Game.h"
#include "Core/Representation/World.h"
int main()
{
    std::shared_ptr<sf::RenderWindow> gWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024,1024),"Test");
    gWindow->setFramerateLimit(60);
    gWindow->clear();
    DungeonRunner::Game *newGame = new DungeonRunner::Game(gWindow);
    while (gWindow->isOpen()){

        gWindow->clear();
        newGame->update();
        gWindow->display();
    }

    return 0;
}