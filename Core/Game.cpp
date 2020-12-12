//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Game.h"


DungeonRunner::Game::Game(const std::shared_ptr<sf::RenderWindow> &gameWindow) : gameWindow(gameWindow) {
   gameWorld = gameFactory.createWorld(gameWindow,4,25);
   gameView = sf::View(sf::Vector2f(gameWindow->getSize().x/2.0,0),sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
   gameView.setCenter(gameWindow->getSize().x/2.0,gameWindow->getSize().y/2.0);
   gameWorld->update(gameView);
   std::shared_ptr<sf::Texture> maleTex = std::make_shared<sf::Texture>();
   maleTex->loadFromFile("../Resources/characterSprites/maleCharacter.png");
   characterTex.push_back(maleTex);
   createPlayer();
}

void DungeonRunner::Game::update() {
    sf::Event event;
    while (gameWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            gameWindow->close();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        gamePlayer->move(0,-5);
        if(gamePlayer->getPos().y<=gameView.getCenter().y)
            pauseView = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        gamePlayer->move(0,+5);
        pauseView = true;
    }
    if(!pauseView) gameView.setCenter(gameWindow->getSize().x/2.0,gamePlayer->getPos().y);
    gameWorld->update(gameView);
    gamePlayer->update(gameView);
    gameWindow->setView(gameView);
}

void DungeonRunner::Game::createPlayer() {
    std::shared_ptr<sf::RectangleShape> player = std::make_shared<sf::RectangleShape>(sf::Vector2f(gameWindow->getSize().x/8.0,gameWindow->getSize().y/8.0));
    std::shared_ptr<sf::Vector2u> playerSize = std::make_shared<sf::Vector2u>(576/12.0,576/8.0);
    std::shared_ptr<sf::IntRect> uvRect = std::make_shared<sf::IntRect>();
    uvRect->width = playerSize->x;
    uvRect->height = playerSize->y;
    uvRect->left = uvRect->width*7;
    uvRect->top = uvRect->height*3;
    player->setPosition((gameWindow->getSize().x/8.0)*2,gameWindow->getSize().y-gameWindow->getSize().y/8.0);
    player->setTextureRect(*uvRect);
    player->setTexture(&*characterTex[0]);
    gamePlayer = gameFactory.createPlayer(gameWindow,player,characterTex[0],uvRect);
}
