//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Game.h"
#include "Logic/Collision.h"

DungeonRunner::Game::Game(const std::shared_ptr<sf::RenderWindow> &gameWindow) : gameWindow(gameWindow) {
   gameWorld = gameFactory.createWorld(gameWindow,4,14);
   gameView = sf::View(sf::Vector2f(gameWindow->getSize().x/2.0,0),sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
   gameView.setCenter(gameWindow->getSize().x/2.0,gameWindow->getSize().y/2.0);
   gameWorld->update();
   gameEntities.insert(gameEntities.end(),gameWorld->getObstacles().begin(),gameWorld->getObstacles().end());
   std::shared_ptr<sf::Texture> maleTex = std::make_shared<sf::Texture>();
   maleTex->loadFromFile("../Resources/characterSprites/maleCharacter.png");
   characterTex.push_back(maleTex);
   createPlayer();
   gameEntities.push_back(gamePlayer);
   std::shared_ptr<Entity> Wall1 = AbstractFactory::createCollider(std::pair<float,float>(-1.25,-7),std::pair<float,float>(0.5,1));
   std::shared_ptr<Entity> Wall2 = AbstractFactory::createCollider(std::pair<float,float>(1.25,-7),std::pair<float,float>(0.5,1));
   gameEntities.push_back(Wall1);
   gameEntities.push_back(Wall2);
   viewColliders.push_back(Wall1);
   viewColliders.push_back(Wall2);
}

void DungeonRunner::Game::update() {
    spawnTraps();
    gameWindow->clear();
    manageGameEvents();
    manageTraps();
    managePlayerMovement();
    gameWorld->update();
    gameWorld->display();
    gamePlayer->update();
    gamePlayer->display();
    gameView.setCenter(gameWindow->getSize().x/2.0,gamePlayer->getPos().y-gameWindow->getSize().y/4.0);
    updateViewColliders();
    for(auto &entity:gameEntities){
        if(entity==gamePlayer) continue;
        entity->update();
        entity->display();
    }
    manageCollision(gamePlayer);
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

bool DungeonRunner::Game::isColliding(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2,float push) {
    Collision newCollision(e1);
    return newCollision.checkCollision(e2,push);
}

void DungeonRunner::Game::updateViewColliders() {
    for(auto &collider:viewColliders){
        if(collider->getEPosition().first!=0){
            std::pair<float,float> newPos = collider->getEPosition();
            newPos.second = Transformation::toCoords(gameWindow,gameView.getCenter().x,gameView.getCenter().y).second-collider->getESize().second/2.0;
            collider->setEPosition(newPos);
        }
    }
}

void DungeonRunner::Game::manageCollision(std::shared_ptr<Entity> entity) {
    for(auto &collider:gameEntities){
        if(collider == entity) continue;
        if(isColliding(collider,entity,1)){
            if(collider->getType() == "Sword" and entity == gamePlayer){
                collider->setEPosition(std::pair<float,float>(-3,9));
                gamePlayer->action();
            }
        }
    }
}

void DungeonRunner::Game::managePlayerMovement() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        //gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()*1.005);
        //if(gamePlayer->getPlayerSpeed() >0.01) gamePlayer->setPlayerSpeed(0.01);
        gamePlayer->move(0,gamePlayer->getPlayerSpeed());

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        //gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()/1.005);
        //if(gamePlayer->getPlayerSpeed() < 0.0025) gamePlayer->setPlayerSpeed(0.0025);
        gamePlayer->move(0,-gamePlayer->getPlayerSpeed());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        gamePlayer->move(0.035,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        gamePlayer->move(-0.035,0);
    }
    if(!pauseGame) gamePlayer->move(0,gamePlayer->getPlayerSpeed());
}

void DungeonRunner::Game::manageGameEvents() {
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
                if (obstacle->getType() == "Door" and !doorOpened and !obstacle->isNoclip()){
                    std::pair<float, float> pPos = gamePlayer->getEPosition();
                    std::pair<float, float> oPos = obstacle->getEPosition();
                    if (oPos.second - pPos.second <= 0.6 and oPos.second - pPos.second >0) {
                        if(pPos.first>oPos.first-0.25 and pPos.first<oPos.first+0.25) {
                            obstacle->action();
                            doorOpened = true;
                        }
                    }
                }
            }
        }

    }
}

void DungeonRunner::Game::spawnTraps() {
    std::pair<float, float> pPos = gamePlayer->getEPosition();
    if(Random::generateRandomChance()<0.02 and pPos.second + 1 <7) {
        std::pair<float, float> tPos;
        tPos.first = Random::getInstance().generateRandFloat(-1, 1);
        tPos.second = pPos.second + 0.8;
        std::cout << tPos.first << ", " << tPos.second << std::endl;
        std::shared_ptr<Entity> newTrap = AbstractFactory::createSword(gameWindow);
        newTrap->setEPosition(tPos);
        newTrap->update();
        newTrap->display();
        newTrap->setNoclip(true);
        gameEntities.push_back(newTrap);
    }

}

void DungeonRunner::Game::manageTraps() {
    for(auto &trap:gameEntities){
        if(trap->getType() == "Sword"){
            trap->move(0,-0.01);
        }
    }

}
