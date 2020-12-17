//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_WORLD_H
#define DUNGEONRUNNER_WORLD_H
#include "../Logic/Entity.h"
#include "DoorSFML.h"
#include <SFML/Graphics.hpp>
#include "../Logic/Random.h"
#include "../Logic/Transformation.h"
namespace DungeonRunner {
    class World : public Entity {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        std::shared_ptr<sf::RenderWindow> gameWindow;
        std::pair<int,int> worldSize;
        std::vector<std::vector<std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>>>> world;
        sf::Texture wallTexture;
        std::vector<std::shared_ptr<sf::Texture>> tileTextures;
        std::map<std::string,std::shared_ptr<sf::Texture>> obstacleTextures;
        std::vector<std::shared_ptr<Entity>> obstacles;
        std::shared_ptr<sf::RectangleShape> worldFinish;
        std::shared_ptr<Entity> worldFinishCollider;


    public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        void initWorld();
        std::shared_ptr<sf::Texture> getRandomFloorTile();
        void initTileTex();
        void initSwordTex();
        void initDoorTex();
        void initPillarTex();

        public:
        World(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);

        const std::vector<std::shared_ptr<Entity>> &getObstacles();

        const std::map<std::string, std::shared_ptr<sf::Texture>> &getObstacleTextures() const;

        void update() override;
        void action() override;
        void display() override;


    };
}

#endif //DUNGEONRUNNER_WORLD_H
