#include <iostream>
#include "Core/Game.h"
#include "Core/Representation/World.h"
#include "Core/Logic/Transformation.h"
#include <random>
int main()
{
    std::shared_ptr<sf::RenderWindow> gWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024,1024),"Test",sf::Style::Titlebar|sf::Style::Close);
    gWindow->setFramerateLimit(60);
    gWindow->clear();
    //gWindow->close();
    auto *newGame = new DungeonRunner::Game(gWindow);
    auto start = std::chrono::high_resolution_clock::now();
    double dTime;
    while (gWindow->isOpen()){
        gWindow->clear();
        auto now = std::chrono::high_resolution_clock::now();
        dTime = std::chrono::duration_cast<std::chrono::duration<double>>(now-start).count();
        start = now;
        std::cout << dTime << std::endl;
        newGame->update(dTime);
        gWindow->display();
    }
    return 0;
}