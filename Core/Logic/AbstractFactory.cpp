//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "AbstractFactory.h"


std::shared_ptr<DungeonRunner::World>
DungeonRunner::AbstractFactory::createWorld(std::shared_ptr<sf::RenderWindow> gWindow,int x, int y) {
    return  std::make_shared<DungeonRunner::World>(gWindow,x,y);
}

std::shared_ptr<DungeonRunnerSFML::Player>
DungeonRunner::AbstractFactory::createPlayer(std::shared_ptr<sf::RenderWindow> gWindow,
                                             std::shared_ptr<sf::RectangleShape> player,
                                             std::shared_ptr<sf::Texture> playerTexture,
                                             std::shared_ptr<sf::IntRect> uvRect){
    return std::make_shared<DungeonRunnerSFML::Player>(gWindow,player,playerTexture,uvRect);
}

std::shared_ptr<DungeonRunnerSFML::DoorSFML>
DungeonRunner::AbstractFactory::createDoor(std::shared_ptr<sf::RectangleShape> &door,
                                           std::shared_ptr<sf::RenderWindow> &gWindow,
                                           std::map<std::string, std::shared_ptr<sf::Texture>> &doorState) {
    return std::make_shared<DungeonRunnerSFML::DoorSFML>(door,gWindow,doorState);
}

std::shared_ptr<DungeonRunner::Entity>
DungeonRunner::AbstractFactory::createCollider(const std::pair<float, float> &ePosition,
                                               const std::pair<float, float> &eSize) {
    return std::make_shared<DungeonRunner::Entity>(ePosition,eSize);
}

std::shared_ptr<DungeonRunnerSFML::Sword>
DungeonRunner::AbstractFactory::createSword(std::shared_ptr<sf::RenderWindow> gWindow) {
    return std::make_shared<DungeonRunnerSFML::Sword>(gWindow);
}

std::shared_ptr<DungeonRunnerSFML::AIPlayer>
DungeonRunner::AbstractFactory::createAI(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
                                         std::shared_ptr<sf::RenderWindow> &gWindow) {
    return std::make_shared<DungeonRunnerSFML::AIPlayer>(gameEntities,gWindow);
}

std::shared_ptr<DungeonRunnerSFML::finishLine>
DungeonRunner::AbstractFactory::createFinish(std::shared_ptr<sf::RenderWindow> &gWindow, sf::RectangleShape &finish) {
    return std::make_shared<DungeonRunnerSFML::finishLine>(gWindow,finish);
}

std::shared_ptr<DungeonRunner::Observer> DungeonRunner::AbstractFactory::createObserver(std::string observerName) {
    return std::make_shared<DungeonRunner::Observer>(observerName);
}



