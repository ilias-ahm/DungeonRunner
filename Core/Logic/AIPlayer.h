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
        float aiSpeed;
        std::vector<std::shared_ptr<DungeonRunner::Entity>> gameEntities;
        int dodgeState = 0; // 0 = straight , 1 = left , 2 = right;
        void avoidObstacles();
        void dodgeObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle);
        bool interactObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle);
        bool isDodging = false;
        bool isStuck = false;
        bool stuckResolving = false;
        float getMoveChance();
    public:
        float getAiSpeed() const;
        void run();
        void updateGameEntities(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities);
        int getDodgeState() const;
        void setDodgeState(int dodgeState);
        bool IsStuck() const;
        void setIsStuck(bool isStuck);

        void setAiSpeed(float aiSpeed);
    };
}


#endif //DUNGEONRUNNER_AIPLAYER_H
