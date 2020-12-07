//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_GAME_H
#define DUNGEONRUNNER_GAME_H
#include "Representation/PlayerSFML.h"
#include "Representation/World.h"
#include "Logic/AbstractFactory.h"

namespace DungeonRunner {
    class Game {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        AbstractFactory gameFactory;
        std::shared_ptr<sf::RenderWindow> gameWindow;
        std::shared_ptr<World> gameWorld;
        sf::View gameView;

        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:

        public:
        Game(const std::shared_ptr<sf::RenderWindow> &gameWindow);
        void update();
    };
}

#endif //DUNGEONRUNNER_GAME_H
