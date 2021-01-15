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
        std::shared_ptr<Highscores> gameScores;
        bool finished = false;
        int finishedPlayers = 0;


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:
        /**
         * Creates a new player
         */
        void createPlayer();
        /**
         * Updates view colliders so that players and AI cant move outside
         */
        void updateViewColliders();
        /**
         * checks collision between all other entities
         * @param entity entity to check collisions for
         */
        void manageCollision(std::shared_ptr<Entity> entity);
        /**
         * Moves the player according to delta time to ensure same speed on all fps settings
         * @param dTime
         */
        void managePlayerMovement(double dTime);
        /**
         * Manages game events
         */
        void manageGameEvents();
        /**
         * Spawns swords according to Player/AI in first place
         * @param dTime
         */
        void spawnTraps(float dTime);
        /**
         * moves swords according to delta time to ensure same speed on all fps settings
         * @param dTime
         */
        void manageTraps(double dTime);
        /**
         * Controls all the AI in the current game (moving , avoiding obstacles, checking collision)
         * @param dTime
         */
        void manageAI(float dTime);
        /**
         * Checking collision between two entities
         * @param e1 entity1
         * @param e2 entity2
         * @param push float between 0-1. higher means entity gets pushed easier
         * @return true if entities are colliding
         */
        bool isColliding(std::shared_ptr<Entity> e1,std::shared_ptr<Entity> e2,float push);
        /**
         * Hikers gain score every loop depending on their place
         * @param dTime delta time to ensure the same score gain on all fps settings
         */
        void manageScores(float dTime);
        /**
         * Draws highscores at the end of the game
         */
        void drawHighscores();
        /**
         * Draws playerscore at the top left corner
         */
        void drawPlayerScore();
        void initAI();

    public:
        /**
         * Constructor
         * @param gameWindow SFML Renderwindow
         */
        Game(const std::shared_ptr<sf::RenderWindow> &gameWindow);
        /**
         * Updates the game
         * @param dTime delta time to ensure same product on different fps settings
         */
        void update(double dTime);
        /**
         * Runs the game loop
         */
        void run();



    };
}

#endif //DUNGEONRUNNER_GAME_H
