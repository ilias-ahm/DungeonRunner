#include "Core/Game.h"
#include "Core/Logic/Transformation.h"
#include "Core/Representation/World.h"
#include <iostream>
#include <random>
int main()
{
        std::shared_ptr<sf::RenderWindow> gWindow = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(SCREENSIZE_X, SCREENSIZE_Y), "DungeonRunner", sf::Style::Titlebar | sf::Style::Close);
        gWindow->setFramerateLimit(FPS);
        gWindow->clear();
        auto newGame = DungeonRunner::Game(gWindow);
        newGame.run();
        return 0;
}