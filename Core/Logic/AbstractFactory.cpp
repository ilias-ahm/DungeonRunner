//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "AbstractFactory.h"


std::shared_ptr<DungeonRunner::World> DungeonRunner::AbstractFactory::createWorld(std::shared_ptr<sf::RenderWindow> gWindow,int x, int y) {
    std::shared_ptr<DungeonRunner::World> newWorld = std::make_shared<DungeonRunner::World>(gWindow,x,y);
    return newWorld;
}

std::shared_ptr<DungeonRunnerSFML::Player> DungeonRunner::AbstractFactory::createPlayer(std::shared_ptr<sf::RenderWindow> gWindow,std::shared_ptr<sf::RectangleShape> player,std::shared_ptr<sf::Texture> playerTexture,std::shared_ptr<sf::IntRect> uvRect){
    std::shared_ptr<DungeonRunnerSFML::Player> newPlayer = std::make_shared<DungeonRunnerSFML::Player>(gWindow,player,playerTexture,uvRect);
    return newPlayer;
}

