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
        /**
         * Creates a new world entity
         * @param gWindow -- SFML Renderwindow
         * @param x  worldsize x
         * @param y  worldsize x
         * @return std::shared_ptr<World>
         */
        static std::shared_ptr<World> createWorld(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);
        /**
         * Creates a new player entity
         * @param gWindow  SFML Renderwindow
         * @param player  SFML rectangleshape
         * @param playerTexture -- SFML Texture
         * @param uvRect  SFML IntRect
         * @return std::shared_ptr<DungeonRunnerSFML::Player>
         */
        static std::shared_ptr<DungeonRunnerSFML::Player> createPlayer(std::shared_ptr<sf::RenderWindow> gWindow,std::shared_ptr<sf::RectangleShape> player,std::shared_ptr<sf::Texture> playerTexture,std::shared_ptr<sf::IntRect> uvRect);
        /**
         * Creates a new Door entity
         * @param door  SFML rectangleshape
         * @param gWindow  SFML Renderwindow
         * @param doorState  map containing 'open' and 'closed' door textures
         * @return std::shared_ptr<DungeonRunnerSFML::DoorSFML>
         */
        static std::shared_ptr<DungeonRunnerSFML::DoorSFML> createDoor(std::shared_ptr<sf::RectangleShape> &door,
                                                                       std::shared_ptr<sf::RenderWindow> &gWindow,
                                                                       std::map<std::string, std::shared_ptr<sf::Texture>> &doorState);
        /**
         * Creates a collider (invisible box)
         * @param ePosition
         * @param eSize
         * @return std::shared_ptr<DungeonRunner::Entity>
         */
        static std::shared_ptr<DungeonRunner::Entity> createCollider(const std::pair<float, float> &ePosition,
                                                              const std::pair<float, float> &eSize);
        /**
         * Creates a new sword entity
         * @param gWindow  SFML Renderwindow
         * @return std::shared_ptr<DungeonRunnerSFML::Sword>
         */
        static std::shared_ptr<DungeonRunnerSFML::Sword> createSword(std::shared_ptr<sf::RenderWindow> gWindow);
        /**
         * Creates a new AI entity
         * @param gameEntities
         * @param gWindow -- SFML Renderwindow
         * @return std::shared_ptr<DungeonRunnerSFML::AIPlayer>
         */
        static std::shared_ptr<DungeonRunnerSFML::AIPlayer> createAI(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
                                                                  std::shared_ptr<sf::RenderWindow> &gWindow);
        /**
         *  Creates a finishline entity
         * @param gWindow  SFML Renderwindow
         * @param finish  SFML Rectangleshape
         * @return std::shared_ptr<DungeonRunnerSFML::finishLine>
         */
        static std::shared_ptr<DungeonRunnerSFML::finishLine> createFinish(std::shared_ptr<sf::RenderWindow> &gWindow,sf::RectangleShape &finish);
        /**
         * Creates a new observer
         * @param observerName  This name will appear on the leaderboard
         * @return std::shared_ptr<DungeonRunner::Observer>
         */
        static std::shared_ptr<DungeonRunner::Observer> createObserver(std::string observerName);
        /**
         * Creates a new highScores entity
         * @param filePath  absolute filepath
         * @return std::shared_ptr<DungeonRunner::Highscores>
         */
        static std::shared_ptr<DungeonRunner::Highscores> createHighscores(std::string filePath);
    };
}

#endif //DUNGEONRUNNER_ABSTRACTFACTORY_H
