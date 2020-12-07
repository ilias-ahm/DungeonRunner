//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_ABSTRACTFACTORY_H
#define DUNGEONRUNNER_ABSTRACTFACTORY_H
#include "Entity.h"
#include "../Representation/World.h"
#include "Player.h"
#include "../Representation/PlayerSFML.h"

namespace DungeonRunner {
    class AbstractFactory {
    public:
        std::shared_ptr<World> createWorld(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);
        std::shared_ptr<DungeonRunnerSFML::Player> createPlayer(sf::RectangleShape player,sf::Texture playerTexture,sf::IntRect uvRect);
    };
}

#endif //DUNGEONRUNNER_ABSTRACTFACTORY_H
