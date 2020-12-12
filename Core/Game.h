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
        bool pauseView = true;
        AbstractFactory gameFactory;
        std::shared_ptr<sf::RenderWindow> gameWindow;
        std::shared_ptr<World> gameWorld;
        sf::View gameView;
        std::shared_ptr<DungeonRunnerSFML::Player> gamePlayer;
        std::vector<std::shared_ptr<sf::Texture>> characterTex;

        public:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:

        public:
        Game(const std::shared_ptr<sf::RenderWindow> &gameWindow);
        void createPlayer();
        void update();
        bool isColliding(std::shared_ptr<Entity> e1,std::shared_ptr<Entity> e2);
    };
}

#endif //DUNGEONRUNNER_GAME_H
