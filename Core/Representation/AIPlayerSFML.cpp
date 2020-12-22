//
// Created by Ilias Ahmindach on 18/12/2020.
//

#include "AIPlayerSFML.h"



DungeonRunnerSFML::AIPlayer::AIPlayer(
        std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
        std::shared_ptr<sf::RenderWindow> &gWindow): gameEntities(gameEntities),gWindow(gWindow) {
    aiPlayer = sf::RectangleShape(sf::Vector2f(gWindow->getSize().x/11.0,gWindow->getSize().y/11.0));
    aiPlayer.setFillColor(sf::Color(133,163,212));
    aiPlayer.setFillColor(sf::Color(125,125,125));
    aiTexture.loadFromFile("../Resources/characterSprites/Soldier_01-4.png");
    aiPlayer.setTexture(&aiTexture);
    std::pair<float,float> aiPos(-0.25,-6.7);
    while(true){
        bool correctPos = true;
        for(auto &entity:gameEntities){
            if(entity->getEPosition() == aiPos){
                aiPos.first+=0.5;
                correctPos = false;
            }
        }
        if(correctPos) break;
    }
    ePosition = aiPos;
    std::pair<float,float> tSize = Transformation::toCoords(gWindow,aiPlayer.getSize().x,aiPlayer.getSize().y);
    tSize.first+=Transformation::getWSize().first/2.0;
    tSize.second+=Transformation::getWSize().second/2.0;
    tSize.second = 1 - tSize.second;
    eSize = tSize;
    aiPos = Transformation::toPixel(gWindow,aiPos.first,aiPos.second);
    aiPlayer.setOrigin(aiPlayer.getSize().x/2.0,aiPlayer.getSize().y);
    aiPlayer.setPosition(aiPos.first,aiPos.second);
    aiSpeed = 0.2;
    eType = "AI";
}

void DungeonRunnerSFML::AIPlayer::display() {
    gWindow->draw(aiPlayer);
}

void DungeonRunnerSFML::AIPlayer::update() {
    std::pair<float,float> pixelC = Transformation::toPixel(gWindow, ePosition.first, ePosition.second);
    aiPlayer.setPosition(pixelC.first,pixelC.second);
}

void DungeonRunnerSFML::AIPlayer::setUvRect(const sf::IntRect &uvRect) {
    AIPlayer::uvRect = uvRect;
    aiPlayer.setTextureRect(uvRect);
}

void DungeonRunnerSFML::AIPlayer::run() {
    auto moveChance = getMovechance();
    if(Random::generateRandomChance() <moveChance) aiSpeed*=1.03;
    else aiSpeed/=1.03;
    if(aiSpeed >0.55) aiSpeed = 0.55;
    if(aiSpeed <0.2) aiSpeed = 0.2;
    avoidObstacles();
    if(isStuck and ePosition.first <0 and !stuckResolving){
        dodgeState = 2;
        isDodging = true;
        stuckResolving = true;
    }
    else if(isStuck and ePosition.first >0 and !stuckResolving) {
        dodgeState = 1;
        isDodging = true;
        stuckResolving = true;
    }
    else if(isStuck and ePosition.first == 0){
        dodgeState =2;
        isDodging = true;
    }
    if(isStuck and isDodging and ePosition.first <-0.7){
        dodgeState = 2;
    }
    if(isStuck and isDodging and ePosition.first >0.7){
        dodgeState = 1;
    }
    //std::cout << ePosition.first<< " | isStuck: " << isStuck <<" | dodgeState:"<<dodgeState << " | stuckResolving :"<< stuckResolving<<std::endl;


}

void DungeonRunnerSFML::AIPlayer::avoidObstacles() {
    std::sort(gameEntities.begin(),gameEntities.end(), [](std::shared_ptr<DungeonRunner::Entity> first, std::shared_ptr<DungeonRunner::Entity> second){
        return first->getEPosition().second < second->getEPosition().second;
    });
    //if(stuckResolving) return;
    for(auto &entity:gameEntities){
        if(entity->getType() == "Door" or entity->getType() == "Sword"){
            auto dY = entity->getEPosition().second - ePosition.second;
            auto dX = std::abs(entity->getEPosition().first - ePosition.first);
            if(dY > 0 and dY < 0.6 and dX < entity->getESize().first/2.0 + eSize.first/2.0) {
                if(isDodging and !isStuck) return;
                if(entity->getType() == "Sword" and Random::generateRandomChance() <0.2  and !stuckResolving) {
                    dodgeObstacle(entity);
                    return;
                }
                if(entity->getType() == "Door") {
                    if (dynamic_cast<DoorSFML*> (entity.get())->IsOpen()) continue;
                    if (Random::generateRandomChance() < 0.0025) {
                        if (!interactObstacle(entity) and !stuckResolving) {
                            dodgeObstacle(entity);
                            return;
                        }
                    }
                    if(!stuckResolving) {
                        dodgeObstacle(entity);
                        return;
                    }
                }
            }
        }
    }
    if(!stuckResolving) {
        isDodging = false;
        dodgeState = 0;
    }
}

bool DungeonRunnerSFML::AIPlayer::interactObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle) {
    if(obstacle->getType() == "Door") {
        obstacle->action();
    }
    return true;

}

void DungeonRunnerSFML::AIPlayer::dodgeObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle) {
    if(Random::generateRandomChance() <0.5) dodgeState = 1;
    else dodgeState = 2;
    if(ePosition.first <-0.5) dodgeState = 2;
    if(ePosition.first >0.5) dodgeState = 1;
    isDodging = true;
}

int DungeonRunnerSFML::AIPlayer::getDodgeState() const {
    return dodgeState;
}

void DungeonRunnerSFML::AIPlayer::setDodgeState(int dodgeState) {
    AIPlayer::dodgeState = dodgeState;
}

void
DungeonRunnerSFML::AIPlayer::updateGameEntities(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities) {
    this->gameEntities = gameEntities;
}

bool DungeonRunnerSFML::AIPlayer::IsStuck() const {
    return isStuck;
}

void DungeonRunnerSFML::AIPlayer::setIsStuck(bool isStuck) {
    AIPlayer::isStuck = isStuck;
    if(!isStuck) stuckResolving = false;
}

float DungeonRunnerSFML::AIPlayer::getMovechance() {
    for(auto entity:gameEntities){
        if(entity->getType() == "Player"){
            float dY = entity->getEPosition().second-ePosition.second;
            float moveChance = 0.5f + 0.5f*dY;
            if(moveChance <0) moveChance = 0;
            if(moveChance>1) moveChance = 1;
            if(entity->getEPosition().second > ePosition.second) return moveChance;
            else return 1.0f-moveChance;
        }
    }
    return 0;
}

