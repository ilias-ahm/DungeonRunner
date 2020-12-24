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
#include "../Representation/SwordSFML.h"
#include "../Representation/AIPlayerSFML.h"
#include "../Representation/finishLine.h"
#include "Highscores.h"

namespace DungeonRunner {
    class AbstractFactory {
    public:
        static std::shared_ptr<World> createWorld(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);
        static std::shared_ptr<DungeonRunnerSFML::Player> createPlayer(std::shared_ptr<sf::RenderWindow> gWindow,std::shared_ptr<sf::RectangleShape> player,std::shared_ptr<sf::Texture> playerTexture,std::shared_ptr<sf::IntRect> uvRect);
        static std::shared_ptr<DungeonRunnerSFML::DoorSFML> createDoor(std::shared_ptr<sf::RectangleShape> &door,
                                                                       std::shared_ptr<sf::RenderWindow> &gWindow,
                                                                       std::map<std::string, std::shared_ptr<sf::Texture>> &doorState);
        static std::shared_ptr<DungeonRunner::Entity> createCollider(const std::pair<float, float> &ePosition,
                                                              const std::pair<float, float> &eSize);
        static std::shared_ptr<DungeonRunnerSFML::Sword> createSword(std::shared_ptr<sf::RenderWindow> gWindow);
        static std::shared_ptr<DungeonRunnerSFML::AIPlayer> createAI(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
                                                                  std::shared_ptr<sf::RenderWindow> &gWindow);
        static std::shared_ptr<DungeonRunnerSFML::finishLine> createFinish(std::shared_ptr<sf::RenderWindow> &gWindow,sf::RectangleShape &finish);
        static std::shared_ptr<DungeonRunner::Observer> createObserver(std::string observerName);
        static std::shared_ptr<DungeonRunner::Highscores> createHighscores(std::string filePath);
    };
}

#endif //DUNGEONRUNNER_ABSTRACTFACTORY_H
