//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_GAME_H
#define DUNGEONRUNNER_GAME_H
#include "Representation/PlayerSFML.h"
#include "Representation/World.h"
#include "Logic/AbstractFactory.h"
#include "Logic/Collision.h"
#include "Representation/AIPlayerSFML.h"
#include <chrono>

namespace DungeonRunner {
    class Game {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        bool pauseGame = false;
        AbstractFactory gameFactory;
        std::shared_ptr<sf::RenderWindow> gameWindow;
        std::shared_ptr<World> gameWorld;
        sf::View gameView;
        std::shared_ptr<DungeonRunnerSFML::Player> gamePlayer;
        std::vector<std::shared_ptr<sf::Texture>> characterTex;
        std::vector<std::shared_ptr<Entity>> gameEntities;
        std::vector<std::shared_ptr<Entity>> viewColliders;
        std::vector<std::shared_ptr<DungeonRunnerSFML::AIPlayer>> aiPlayers;
        std::shared_ptr<DungeonRunnerSFML::Animation> playerAnimation;
        std::shared_ptr<DungeonRunnerSFML::Animation> aiAnimation;
        bool finished;
        int finishedPlayers = 0;


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        void createPlayer();
        void updateViewColliders();
        void manageCollision(std::shared_ptr<Entity> entity);
        void managePlayerMovement(double dTime);
        void manageGameEvents();
        void spawnTraps();
        void manageTraps(double dTime);
        void manageAI(float dTime);
        bool isColliding(std::shared_ptr<Entity> e1,std::shared_ptr<Entity> e2,float push);
        void manageScores(float dTime);

    public:
        Game(const std::shared_ptr<sf::RenderWindow> &gameWindow);
        void update(double dTime);
        void run();

        void initAI();

    };
}

#endif //DUNGEONRUNNER_GAME_H
