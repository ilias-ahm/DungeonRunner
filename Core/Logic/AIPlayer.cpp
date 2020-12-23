//
// Created by Ilias Ahmindach on 18/12/2020.
//

#include "AIPlayer.h"

float DungeonRunner::AIPlayer::getAiSpeed() const {
    return aiSpeed;
}

void DungeonRunner::AIPlayer::setAiSpeed(float aiSpeed) {
    AIPlayer::aiSpeed = aiSpeed;
}
void DungeonRunner::AIPlayer::run() {
    auto moveChance = getMoveChance();
    if(Random::generateRandomChance() <moveChance) aiSpeed*=1.03;
    else aiSpeed/=1.03;
    if(aiSpeed >0.6) aiSpeed = 0.6;
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

void DungeonRunner::AIPlayer::avoidObstacles() {
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
                    if (dynamic_cast<DungeonRunnerSFML::DoorSFML*> (entity.get())->IsOpen()) continue;
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

bool DungeonRunner::AIPlayer::interactObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle) {
    if(obstacle->getType() == "Door") {
        obstacle->action();
    }
    return true;

}

void DungeonRunner::AIPlayer::dodgeObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle) {
    if(Random::generateRandomChance() <0.5) dodgeState = 1;
    else dodgeState = 2;
    if(ePosition.first <-0.5) dodgeState = 2;
    if(ePosition.first >0.5) dodgeState = 1;
    isDodging = true;
}
int DungeonRunner::AIPlayer::getDodgeState() const {
    return dodgeState;
}

void DungeonRunner::AIPlayer::setDodgeState(int dodgeState) {
    AIPlayer::dodgeState = dodgeState;
}

void
DungeonRunner::AIPlayer::updateGameEntities(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities) {
    this->gameEntities = gameEntities;
}

bool DungeonRunner::AIPlayer::IsStuck() const {
    return isStuck;
}

void DungeonRunner::AIPlayer::setIsStuck(bool isStuck) {
    AIPlayer::isStuck = isStuck;
    if(!isStuck) stuckResolving = false;
}

float DungeonRunner::AIPlayer::getMoveChance() {
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

