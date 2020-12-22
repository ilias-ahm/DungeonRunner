//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Game.h"

DungeonRunner::Game::Game(const std::shared_ptr<sf::RenderWindow> &gameWindow) : gameWindow(gameWindow) {
   gameWorld = gameFactory.createWorld(gameWindow,4,14);
   gameView = sf::View(sf::Vector2f(gameWindow->getSize().x/2.0,0),sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
   gameView.setCenter(gameWindow->getSize().x/2.0,gameWindow->getSize().y/2.0);
   gameWorld->update();
   gameEntities.insert(gameEntities.end(),gameWorld->getObstacles().begin(),gameWorld->getObstacles().end());
   std::shared_ptr<sf::Texture> maleTex = std::make_shared<sf::Texture>();
   std::shared_ptr<sf::Texture> aiTex = std::make_shared<sf::Texture>();
   maleTex->loadFromFile("../Resources/characterSprites/Male_16-1.png");
   aiTex->loadFromFile("../Resources/characterSprites/Soldier_01-4.png");
   characterTex.push_back(maleTex);
   createPlayer();
   initAI();
   gameEntities.push_back(gamePlayer);
   playerAnimation = std::make_shared<DungeonRunnerSFML::Animation>(maleTex,sf::Vector2u(3,4));
   aiAnimation = std::make_shared<DungeonRunnerSFML::Animation>(aiTex,sf::Vector2u(3,4));
   std::shared_ptr<Entity> Wall1 = AbstractFactory::createCollider(std::pair<float,float>(-1.25,-7),std::pair<float,float>(0.5,14));
   std::shared_ptr<Entity> Wall2 = AbstractFactory::createCollider(std::pair<float,float>(1.25,-7),std::pair<float,float>(0.5,14));
   //std::shared_ptr<Entity> Wall3 = AbstractFactory::createCollider(std::pair<float,float>(0,-6),std::pair<float,float>(4,0.125));
   //std::shared_ptr<Entity> Wall4 = AbstractFactory::createCollider(std::pair<float,float>(0,-7.125),std::pair<float,float>(4,0.125));
   gameEntities.push_back(Wall1);
   gameEntities.push_back(Wall2);
   //gameEntities.push_back(Wall3);
   //gameEntities.push_back(Wall4);
   viewColliders.push_back(Wall1);
   viewColliders.push_back(Wall2);
   //viewColliders.push_back(Wall3);
   //viewColliders.push_back(Wall4);
}

void DungeonRunner::Game::update(double dTime) {
    spawnTraps();
    gameWindow->clear();
    manageGameEvents();
    manageTraps(dTime);
    manageCollision(gamePlayer);
    managePlayerMovement(dTime);
    for(auto &ai:aiPlayers){
        ai->updateGameEntities(gameEntities);
        manageCollision(ai);
    }
    manageAI(dTime);
    gameWorld->update();
    gameWorld->display();
    for(auto &ai:aiPlayers){
        aiAnimation->update(3,dTime,true,0.5/ai->getAiSpeed());
        ai->setUvRect(aiAnimation->getUvRect());
        ai->update();
        ai->display();
    }
    gamePlayer->update();
    playerAnimation->update(3,dTime,true,0.15/gamePlayer->getPlayerSpeed());
    gamePlayer->setUvRect(std::make_shared<sf::IntRect>(playerAnimation->getUvRect()));
    gamePlayer->display();
    auto mapCoords = Transformation::toPixel(gameWindow,0,6.5);
    if(gamePlayer->getPos().y < mapCoords.second+gameWindow->getSize().y/2.0-gameWindow->getSize().y/4.0) gameView.setCenter(gameWindow->getSize().x/2.0,mapCoords.second);
    else gameView.setCenter(gameWindow->getSize().x/2.0,gamePlayer->getPos().y-gameWindow->getSize().y/4.0);
    updateViewColliders();

    for(auto &entity:gameEntities){
        if(entity==gamePlayer or entity->getType() == "AI") continue;
        entity->update();
        entity->display();
    }
    gameWindow->setView(gameView);
}

void DungeonRunner::Game::createPlayer() {
    std::shared_ptr<sf::RectangleShape> player = std::make_shared<sf::RectangleShape>(sf::Vector2f(gameWindow->getSize().x/11.0,gameWindow->getSize().y/11.0));
    std::shared_ptr<sf::Vector2u> playerSize = std::make_shared<sf::Vector2u>(32,32);
    std::shared_ptr<sf::IntRect> uvRect = std::make_shared<sf::IntRect>();
    uvRect->width = playerSize->x;
    uvRect->height = playerSize->y;
    uvRect->left = uvRect->width*1;
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
        std::pair<float,float> newPos = collider->getEPosition();
        if(collider->getEPosition().first!=0){
            //newPos.second = Transformation::toCoords(gameWindow,gameView.getCenter().x,gameView.getCenter().y).second-collider->getESize().second/2.0;
            //collider->setEPosition(newPos);
        }
        else{
            if(newPos.second < gamePlayer->getEPosition().second){
                float newY = gameView.getCenter().y+gameView.getSize().y/2.0;
                newPos.second = Transformation::toCoords(gameWindow,gameView.getCenter().x,newY).second-collider->getESize().second;
                collider->setEPosition(newPos);
            }
            else{
                float newY = gameView.getCenter().y-gameView.getSize().y/2.0;
                newPos.second = Transformation::toCoords(gameWindow,gameView.getCenter().x,newY).second;
                collider->setEPosition(newPos);
            }
        }
    }
}

void DungeonRunner::Game::manageCollision(std::shared_ptr<Entity> entity) {
    for(auto &collider:gameEntities){
        float push = 1;
        if(collider == entity) continue;
        if(entity->getType() == "AI" and collider->getType() == "Player") push =0.5;
        if(collider->getType() == "AI" and entity->getType() == "Player") push =0.5;
        if(collider->getType() == "AI" and entity->getType() == "AI") push =0.5;
        if(isColliding(collider,entity,push)){
            if(collider->getType() == "Sword" and (entity->getType() == "Player" or entity->getType() == "AI")){
                collider->setEPosition(std::pair<float,float>(-3,9));
                entity->action();
            }
            continue;
        }
    }
}

void DungeonRunner::Game::managePlayerMovement(double dTime) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()*1.01);
        if(gamePlayer->getPlayerSpeed()*1.01 > 0.5) gamePlayer->setPlayerSpeed(0.5);
        //gamePlayer->move(0,gamePlayer->getPlayerSpeed()*dTime);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        //gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()/1.01);
        //if(gamePlayer->getPlayerSpeed()/1.01 < 0.2) gamePlayer->setPlayerSpeed(0.2);

        gamePlayer->move(0,-gamePlayer->getPlayerSpeed()*1.5*dTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        gamePlayer->move(2*dTime,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        gamePlayer->move(-2*dTime,0);
    }
    if(!pauseGame) gamePlayer->move(0,gamePlayer->getPlayerSpeed()*dTime);
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
            for (auto &obstacle:gameEntities) {
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
    std::pair<float, float> aiPos = aiPlayers[0]->getEPosition();
    for(auto &ai:aiPlayers){
        if(ai->getEPosition().second > aiPos.second) aiPos = ai->getEPosition();
    }
    if(aiPos.second > pPos.second) pPos =aiPos;
    if(Random::generateRandomChance()<0.013 and pPos.second + 1 <7) {
        std::pair<float, float> tPos;
        tPos.first = Random::getInstance().generateRandFloat(-1, 1);
        tPos.second = pPos.second + 0.8;
        std::shared_ptr<Entity> newTrap = AbstractFactory::createSword(gameWindow);
        newTrap->setEPosition(tPos);
        newTrap->update();
        newTrap->display();
        newTrap->setNoclip(true);
        gameEntities.push_back(newTrap);
    }

}

void DungeonRunner::Game::manageTraps(double dTime) {
    for(auto &trap:gameEntities){
        if(trap->getType() == "Sword"){
            trap->move(0,-dTime*0.8);
        }
    }

}

void DungeonRunner::Game::initAI() {
    for(int i=1;i!=4;i++){
        auto newAI = AbstractFactory::createAI(gameEntities,gameWindow);
        gameEntities.push_back(newAI);
        aiPlayers.push_back(newAI);
    }

}

void DungeonRunner::Game::run() {
    auto start = std::chrono::high_resolution_clock::now();
    double dTime;
    while (gameWindow->isOpen()){
        auto bpos0 = aiPlayers[0]->getEPosition();
        auto bpos1 = aiPlayers[1]->getEPosition();
        auto bpos2 = aiPlayers[2]->getEPosition();
        gameWindow->clear();
        auto now = std::chrono::high_resolution_clock::now();
        dTime = std::chrono::duration_cast<std::chrono::duration<double>>(now-start).count();
        if(dTime>1/60.0f){
            dTime = 1/60.0f;
        }
        start = now;
        update(dTime);
        gameWindow->display();
        auto apos0 = aiPlayers[0]->getEPosition();
        auto apos1 = aiPlayers[1]->getEPosition();
        auto apos2 = aiPlayers[2]->getEPosition();
        auto checkPos0 = std::abs(bpos0.second - apos0.second);
        auto checkPos1 = std::abs(bpos1.second - apos1.second);
        auto checkPos2 = std::abs(bpos2.second - apos2.second);
        if( checkPos0 +0.000001< aiPlayers[0]->getAiSpeed()*dTime) aiPlayers[0]->setIsStuck(true);
        else aiPlayers[0]->setIsStuck(false);
        if( checkPos1 +0.000001< aiPlayers[1]->getAiSpeed()*dTime) aiPlayers[1]->setIsStuck(true);
        else aiPlayers[1]->setIsStuck(false);
        if( checkPos2 +0.000001< aiPlayers[2]->getAiSpeed()*dTime) aiPlayers[2]->setIsStuck(true);
        else aiPlayers[2]->setIsStuck(false);
    }
}

void DungeonRunner::Game::manageAI(float dTime) {
    for(auto &ai:aiPlayers){
        manageCollision(ai);
        ai->run();
        ai->move(0,ai->getAiSpeed()*dTime);
        for(auto &checkai:aiPlayers){
            manageCollision(checkai);
        }
        if(ai->getDodgeState() == 1){
            ai->move(-2*dTime,0);
        }
        else if(ai->getDodgeState() == 2){
            ai->move(2*dTime,0);
        }
        for(auto &checkai:aiPlayers){
            manageCollision(checkai);
        }
        manageCollision(gamePlayer);



    }
}
