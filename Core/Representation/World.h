//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_WORLD_H
#define DUNGEONRUNNER_WORLD_H
#include "../Logic/Entity.h"
#include <SFML/Graphics.hpp>
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
        sf::RectangleShape wall1;
        sf::RectangleShape wall2;


        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        void initWorld();
        std::shared_ptr<sf::Texture> getRandomFloorTile();
        void initTileTex();

        public:
        World(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y);
        void update(sf::View);


    };
}

#endif //DUNGEONRUNNER_WORLD_H
