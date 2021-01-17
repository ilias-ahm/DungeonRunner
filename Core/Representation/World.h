//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_WORLD_H
#define DUNGEONRUNNER_WORLD_H
#include "../Logic/Entity.h"
#include "../Logic/Random.h"
#include "../Logic/Transformation.h"
#include "DoorSFML.h"
#include "finishLine.h"
#include <SFML/Graphics.hpp>

namespace DungeonRunner {
class World : public Entity
{
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                          Variables //
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
        std::shared_ptr<sf::RenderWindow> gameWindow;
        std::pair<int, int> worldSize;
        std::vector<std::vector<std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>>>> worldTiles;
        sf::Texture wallTexture;
        std::vector<std::shared_ptr<sf::Texture>> tileTextures;
        std::map<std::string, std::shared_ptr<sf::Texture>> obstacleTextures;
        std::vector<std::shared_ptr<Entity>> worldEntities;
        std::shared_ptr<DungeonRunnerSFML::finishLine> worldFinish;

public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                          Functions //
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
        /**
         * Initializes map
         */
        void initWorld();
        /**
         * Returns random floortile texture [1-8]
         * @return
         */
        std::shared_ptr<sf::Texture> getRandomFloorTexture();
        /**
         * Loads all tile textures
         */
        void initTileTex();
        /**
         * Loads sword texture(s)
         */
        void initSwordTex();
        /**
         * Loads Door textures
         */
        void initDoorTex();
        void initPillarTex(); // UNUSED

public:
        /**
         * Constructor
         * @param gWindow SFML Renderwindow
         * @param x worldsize x
         * @param y worldsize y
         */
        World(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);
        /**
         * Returns world entities
         * @return
         */
        const std::vector<std::shared_ptr<Entity>>& getWorldEntities();
        void update() override; // UNUSED
        void action() override; // UNUSED
        /**
         * Displays worldmap on SFML Renderwindow
         */
        void display() override;
};
} // namespace DungeonRunner

#endif // DUNGEONRUNNER_WORLD_H
