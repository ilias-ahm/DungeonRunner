//
// Created by Ilias Ahmindach on 18/12/2020.
//

#ifndef DUNGEONRUNNER_AIPLAYER_H
#define DUNGEONRUNNER_AIPLAYER_H
#include "Entity.h"
#include "../Representation/DoorSFML.h"
namespace DungeonRunner {
    class AIPlayer: public Entity {
    protected:
        float aiSpeed; // Float between 0.2 - 0.6
        std::vector<std::shared_ptr<DungeonRunner::Entity>> gameEntities; // All entities in the game
        int dodgeState = 0; // 0 = straight , 1 = left , 2 = right;
        /**
         * Contains the actions and intelligence for the AI's to avoid obstacles and other players (move left and right or interact (yell) with obstacles)
         */
        void avoidObstacles();
        /**
         * dodges an obstacle
         * @param obstacle -- Entity to dodge
         */
        void dodgeObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle);
        /**
         *
         * @param obstacle -- obstacle tot interact with
         * @return boolean on whether or not the interaction was succesful (opened door)
         */
        bool interactObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle);
        bool isDodging = false;
        bool isStuck = false;
        bool stuckResolving = false;
        /**
         * Chance to speedup/slow down, changes dynamically. Chance to speedup increases if player is further ahead.
         * @return float between 0-1
         */
        float getMoveChance();
    public:
        /**
         * Getter for AI Speed
         * @return AI Speed
         */
        float getAiSpeed() const;
        /**
         * Moves the AI and checks what to avoid and how to avoid obstacles
         */
        void run();
        /**
         * Setter for gameEntities
         * @param gameEntities -- all entities in the game
         */
        void updateGameEntities(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities);
        /**
         * Getter for dodgeState
         * @return integer between 0-2
         */
        int getDodgeState() const;
        /**
         * Setter for isStuck parameter
         * @param isStuck -- 1: Ai is stuck 0: ai is not stuck
         */
        void setIsStuck(bool isStuck);
        /**
         * setter for AI Speed
         * @param aiSpeed
         */
        void setAiSpeed(float aiSpeed);
    };
}


#endif //DUNGEONRUNNER_AIPLAYER_H
