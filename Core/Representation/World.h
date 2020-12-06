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


        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        void initWorld();
        public:
        World(int x, int y);

        std::string getRandomFloorTile();
    };
}

#endif //DUNGEONRUNNER_WORLD_H
