//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Game.h"


DungeonRunner::Game::Game(const std::shared_ptr<sf::RenderWindow> &gameWindow) : gameWindow(gameWindow) {
   gameWorld = gameFactory.createWorld(gameWindow,4,25);
   gameView = sf::View(sf::Vector2f(gameWindow->getSize().x/2.0,0),sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
   gameView.setCenter(gameWindow->getSize().x/2,gameWindow->getSize().y/2);
   gameWorld->update(gameView);
}

void DungeonRunner::Game::update() {
    sf::Event event;
    while (gameWindow->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            gameWindow->close();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        gameView.move(0,-5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        gameView.move(0,+5);
    }
    gameWorld->update(gameView);
    gameWindow->setView(gameView);
}
