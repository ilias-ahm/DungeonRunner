//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Game.h"


DungeonRunner::Game::Game(const std::shared_ptr<sf::RenderWindow> &gameWindow) : gameWindow(gameWindow) {
   gameWorld = gameFactory.createWorld(gameWindow,4,14);
   gameView = sf::View(sf::Vector2f(gameWindow->getSize().x/2.0,0),sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
   gameView.setCenter(gameWindow->getSize().x/2.0,gameWindow->getSize().y/2.0);
   gameWorld->update();
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
        if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Key::P){
            pauseGame = !pauseGame;
        }
        if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Space) {
            bool doorOpened = false;
            for (auto &obstacle:gameWorld->getObstacles()) {
                if (obstacle->getType() == "Door" and !doorOpened) {
                    std::pair<float, float> pPos = gamePlayer->getEPosition();
                    std::pair<float, float> oPos = obstacle->getEPosition();
                    std::cout << oPos.second - pPos.second <<" | " << pPos.first << ", " << oPos.first <<std::endl;

                    if (oPos.second - pPos.second <= 0.6 and oPos.second - pPos.second >0) {
                        if(pPos.first>oPos.first-0.50 and pPos.first<oPos.first+0.50) {
                            obstacle->action();
                            doorOpened = true;
                        }
                    }
                }
            }
            std::cout << "-------------------------\n";
        }

    }
    if(gamePlayer->getPos().y<=gameView.getCenter().y+gameWindow->getSize().y/8.0)
        pauseView = false;
    else{
        pauseView = true;
        gameView.setCenter(gameWindow->getSize().x/2.0,gameWindow->getSize().y/2.0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()*1.005);
        if(gamePlayer->getPlayerSpeed() >0.01) gamePlayer->setPlayerSpeed(0.01);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()/1.005);
        if(gamePlayer->getPlayerSpeed() < 0.0025) gamePlayer->setPlayerSpeed(0.0025);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        gamePlayer->move(0.045,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        gamePlayer->move(-0.045,0);
    }
    gameWindow->clear();
    if(!pauseGame) gamePlayer->move(0,gamePlayer->getPlayerSpeed());
    if (!pauseView) gameView.setCenter(gameWindow->getSize().x/2.0,gamePlayer->getPos().y-gameWindow->getSize().y/8.0);
    gameWorld->update();
    gamePlayer->update();
    for(auto &obstacle:gameWorld->getObstacles()){
        obstacle->update();
        obstacle->display();
    }
    gameWindow->setView(gameView);
}

void DungeonRunner::Game::createPlayer() {
    std::shared_ptr<sf::RectangleShape> player = std::make_shared<sf::RectangleShape>(sf::Vector2f(gameWindow->getSize().x/12.0,gameWindow->getSize().y/8.0));
    std::shared_ptr<sf::Vector2u> playerSize = std::make_shared<sf::Vector2u>(576/12.0,576/8.0);
    std::shared_ptr<sf::IntRect> uvRect = std::make_shared<sf::IntRect>();
    uvRect->width = playerSize->x;
    uvRect->height = playerSize->y;
    uvRect->left = uvRect->width*7;
    uvRect->top = uvRect->height*3;
    player->setTextureRect(*uvRect);
    player->setTexture(&*characterTex[0]);
    gamePlayer = gameFactory.createPlayer(gameWindow,player,characterTex[0],uvRect);
}

bool DungeonRunner::Game::isColliding(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2) {
    return false;
}
