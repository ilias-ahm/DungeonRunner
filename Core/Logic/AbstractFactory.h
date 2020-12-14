//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_ABSTRACTFACTORY_H
#define DUNGEONRUNNER_ABSTRACTFACTORY_H
#include "Entity.h"
#include "../Representation/World.h"
#include "Player.h"
#include "../Representation/PlayerSFML.h"
#include "Transformation.h"
namespace DungeonRunner {
    class AbstractFactory {
    public:
        std::shared_ptr<World> createWorld(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);
        std::shared_ptr<DungeonRunnerSFML::Player> createPlayer(std::shared_ptr<sf::RenderWindow> gWindow,std::shared_ptr<sf::RectangleShape> player,std::shared_ptr<sf::Texture> playerTexture,std::shared_ptr<sf::IntRect> uvRect);
        std::shared_ptr<Transformation> createTransformation(std::shared_ptr<sf::RenderWindow> gWindow,int x, int y);
    };
}

#endif //DUNGEONRUNNER_ABSTRACTFACTORY_H
