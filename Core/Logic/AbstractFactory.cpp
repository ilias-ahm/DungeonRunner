//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "AbstractFactory.h"


std::shared_ptr<DungeonRunner::World> DungeonRunner::AbstractFactory::createWorld(int x, int y) {
    std::shared_ptr<DungeonRunner::World> newWorld = std::make_shared<DungeonRunner::World>(x,y);
    return newWorld;
}

std::shared_ptr<DungeonRunnerSFML::Player> DungeonRunner::AbstractFactory::createPlayer(sf::RectangleShape player, sf::Texture playerTexture, sf::IntRect uvRect) {
    std::shared_ptr<DungeonRunnerSFML::Player> newPlayer = std::make_shared<DungeonRunnerSFML::Player>(player,playerTexture,uvRect);
    return newPlayer;
}
